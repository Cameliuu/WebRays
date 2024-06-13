import argparse
import os
from bs4 import BeautifulSoup
from termcolor import colored


def check_html_file(html_file):
    if not html_file.endswith('.html'):
        print(colored(f'The file {html_file} is not an HTML file', 'red'))
        exit(-1)
    if not os.path.isfile(html_file):
        print(colored(f'The file {html_file} does not exist', 'red'))
        exit(-1)


def main():
    try:
        parser = argparse.ArgumentParser()
        parser.add_argument("--html-file", help="The HTML file that needs to be modified")
        parser.add_argument("--scripts-folder", help="The folder from which the scripts should be loaded",
                            default="Scripts")
        args = parser.parse_args()

        if not args.html_file:
            print("Please provide an HTML file")
            exit(-1)

        check_html_file(args.html_file)

        with open(args.html_file, 'r', encoding='utf-8') as html_file:
            soup = BeautifulSoup(html_file, 'html.parser')

        if not soup.body:
            print(colored("[!] The HTML file does not have a <body> tag. Creating one...", color="yellow"))
            if not soup.html:
                soup.append(soup.new_tag('html'))
            soup.html.append(soup.new_tag('body'))

        for script in os.listdir(args.scripts_folder):
            if script.endswith(".js"):
                new_content = soup.new_tag('script', src=f"{args.scripts_folder}/{script}")
                soup.body.append(new_content)

        with open(args.html_file, 'w', encoding='utf-8') as html_file:
            html_file.write(str(soup))

        print(colored("The HTML file has been modified", color="green"))

    except Exception as e:
        print(colored(f"An error occurred: {e}", "red"))
        input("press any key to exit");
        exit(-1)


if __name__ == "__main__":
    main()
