import xml.etree.ElementTree as ET
from typing import Generator
from pathlib import PurePath, Path
import argparse

from google.protobuf.message import Message
from proto.web_pb2 import Article
from google.protobuf.text_format import PrintMessage
from google.protobuf.timestamp_pb2 import Timestamp
from datetime import datetime

BACKUP_FILE_PATH = PurePath(
    'data/wordpress_backups/site.wordpress.2021-10-25.000.xml')
WP_TAG = 'http://wordpress.org/export/1.2/'
CONTENT_TAG = 'http://purl.org/rss/1.0/modules/content/'


def get_post_type_for_item(element: ET.Element):
    for child in element:
        if child.tag != f'{{{WP_TAG}}}post_type':
            continue
        return child.text
    return 'none'


def get_articles_from_root(
        root: ET.Element) -> Generator[ET.Element, None, None]:
    channel = root[0]
    if not channel or channel.tag != "channel":
        raise Exception("Missing channel tag.")
    for child in channel:
        if child.tag != 'item':
            continue
        if get_post_type_for_item(child) != 'post':
            continue
        yield child


def get_article_from_element(element: ET.Element) -> Article:
    article = Article()
    for child in element:
        if child.tag == 'title':
            article.title = child.text
        if child.tag == f'{{{WP_TAG}}}post_date_gmt':
            parsed_datetime = datetime.strptime(child.text,
                                                '%Y-%m-%d %H:%M:%S')
            article.create_ts.FromDatetime(parsed_datetime)
        if child.tag == f'{{{CONTENT_TAG}}}encoded':
            article.content = child.text
    return article


def dump_article_to_files(article: Article, target_path: Path,
                          id: int) -> None:
    metadata_path = target_path.joinpath(f'{id}_metadata.textproto')
    content_path = target_path.joinpath(f'{id}_content.md')
    with content_path.open('w') as f:
        f.write(article.content)
    with metadata_path.open('w') as f:
        article.content = ''
        PrintMessage(article, f, as_utf8=True)


if __name__ == "__main__":

    parser = argparse.ArgumentParser(description='Process some integers.')
    parser.add_argument('destination_path', type=Path)
    args = parser.parse_args()

    tree = ET.parse(BACKUP_FILE_PATH)
    root = tree.getroot()
    for i, article in enumerate(get_articles_from_root(root)):
        article = get_article_from_element(article)
        dump_article_to_files(article, args.destination_path, i)
