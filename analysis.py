import re
import os

def split_mikrotik_config(file_content):
    sections = {}
    section_name = None
    for line in file_content.splitlines():
        if re.match(r'^/', line) and not re.match(r'^#',line):
            section_name = line.strip()
            sections[section_name] = []
        elif section_name:
            sections[section_name].append(line)
    return sections

def get_files_with_extension(folder_path, extension):
    files = []
    for file in os.listdir(folder_path):
        if file.endswith(extension):
            files.append(file)
    return files

def find_missing_ips(ip_list, directory):
    files = os.listdir(directory)
    file_ips = [os.path.splitext(file)[0] for file in files if file.endswith('.rsc')]
    return list(filter(lambda ip: ip not in file_ips, ip_list))