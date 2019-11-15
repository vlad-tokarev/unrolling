import os
from settings import TSVC_PATH


def delete_files(path):
    files = os.listdir(path)
    for item in files:
        if item.endswith(".tpips"):
            os.remove(os.path.join(path, item))


delete_files(TSVC_PATH)
