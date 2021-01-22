import argparse
import re
import subprocess
import urllib.parse

RE_LINES_COV = re.compile('([0-9]+) of ([0-9]+) lines')
RE_FUNCS_COV = re.compile('([0-9]+) of ([0-9]+) functions')


def get_color(percent):
    if percent <= 80: return 'red'
    if percent <= 85: return 'yellow'
    if percent <= 90: return 'yellowgreen'
    if percent <= 95: return 'green'
    return 'brightgreen'


def extract_coverage(pattern, stdout):
    match = pattern.search(stdout)
    covered, total = float(match.group(1)), float(match.group(2))
    percent = int(100.0 * covered / total + 0.5)
    color = get_color(percent)
    return dict(
        color = color,
        covered = covered,
        percent = str(percent),
        total = total,
    )

def download(filename, label, coverage, color):
    label = urllib.parse.quote(label)
    coverage = urllib.parse.quote(coverage)
    url = f"https://img.shields.io/badge/{label}-{coverage}-{color}"
    subprocess.check_call(['curl', url, '-o', filename])


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument(
        'coverage_info',
        help = "The input .info file to process with lcov",
    )

    args = parser.parse_args()

    out = subprocess.check_output(['lcov', '--summary', args.coverage_info]).decode('utf-8')

    lines = extract_coverage(RE_LINES_COV, out)
    funcs = extract_coverage(RE_FUNCS_COV, out)

    download(
        'coverage/coverage_lines.svg',
        'Line Coverage',
        lines['percent'],
        lines['color'],
    )

    download(
        'coverage/coverage_funcs.svg',
        'Function Coverage',
        funcs['percent'],
        funcs['color'],
    )

if __name__ == "__main__":
    main()
