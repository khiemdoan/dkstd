import re
from pathlib import Path


def update_version(file_path):
    with open(file_path, 'r', encoding='utf-8') as infile:
        content = infile.read()

    dates = re.findall(r'\d{4}-\d{2}-\d{2}', content)
    if len(dates) == 0:
        return
    dates = sorted(dates, reverse=True)
    last_date = dates[0]

    content = re.sub(r'(.+modified:\s+)(\d{4}-\d{2}-\d{2})', r'\g<1>' + last_date, content)

    print(f'{file_path} - {last_date}')

    with open(file_path, 'w', encoding='utf-8') as outfile:
        outfile.write(content)


if __name__ == '__main__':
    current_dir = Path(__file__).parent
    for hpp_file in current_dir.glob('*.hpp'):
        update_version(hpp_file)
