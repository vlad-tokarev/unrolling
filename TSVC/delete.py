import os


def delete_files(path, extension):
    files = os.listdir(path)
    for item in files:
        if item.endswith(extension):
            os.remove(os.path.join(path, item))
