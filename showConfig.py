import sys
from PyQt5.QtWidgets import QApplication, QMainWindow, QTreeWidget, QTreeWidgetItem

def display_config_sections(file_path):
    app = QApplication(sys.argv)
    window = QMainWindow()
    tree = QTreeWidget(window)
    window.setCentralWidget(tree)

    # Загружаем данные из файла и разбиваем их на секции
    sections = {}
    with open(file_path) as f:
        current_section = ''
        for line in f:
            if line.startswith('#'):
                continue
            if line.startswith('/'):
                current_section = line.strip()
                sections[current_section] = []
            else:
                sections[current_section].append(line.strip())

    for section in sections:
        # Создаем элемент дерева для секции
        section_item = QTreeWidgetItem(tree)
        section_item.setText(0, section)
        # Разбиваем секцию на строки
        section_lines = sections[section]
        for line in section_lines:
            if line.startswith('#'):
                continue
            # Создаем элемент дерева для строки
            line_item = QTreeWidgetItem(section_item)
            line_item.setText(0, line)
    window.show()
    sys.exit(app.exec_())


