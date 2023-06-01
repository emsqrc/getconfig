# ips.py
import re
import os
def get_ips_from_file(file_path):
    """
    Читает файл и возвращает список IP-адресов
    """
    ips = []
    with open(file_path, 'r') as f:
        for line in f:
            # Используйте регулярное выражение для извлечения IP-адресов из строки
            match = re.search( r'\b\d{1,3}\.\d{1,3}\.\d{1,3}\.\d{1,3}\b', line)
            if match:
                ips.append(match.group())
    return ips

def remove_rsc_files(folder_path):
    """
    This function takes the folder path as input and deletes all the files with '.rsc' extension in the folder.
    :param folder_path: The path to the folder where the '.rsc' files need to be deleted
    :return: None
    """
    # List all the files in the folder
    files = os.listdir(folder_path)
    # Loop through each file in the folder
    for file in files:
        # Get the full file path
        file_path = os.path.join(folder_path, file)
        # Check if the file is a regular file and has '.rsc' extension
        if os.path.isfile(file_path) and file.endswith('.rsc'):
            # If the file is a '.rsc' file, delete it
            os.remove(file_path)