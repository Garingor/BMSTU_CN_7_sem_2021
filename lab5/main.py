import argparse
import smtplib
import os
from email.message import EmailMessage
import datetime
import time


def parse_args():
    parser = argparse.ArgumentParser(description='SMTP')
    parser.add_argument('to', help='Set to')
    parser.add_argument('from', help='Set from')
    parser.add_argument('password', help='Set password')
    return parser.parse_args()


def main():
    args = vars(parse_args())

    msg = EmailMessage()

    msg['From'] = args['from']
    msg['To'] = args['to']
    msg['Subject'] = input('Subject: ')

    print('\nBody:')

    msg.set_content(input(''))

    date_entry = input('Enter a date in YYYY-MM-DD-hour-minute format: ')
    year, month, day, hour, minute = map(int, date_entry.split('-'))
    date1 = datetime.datetime(year, month, day, hour, minute)


    print("Print filename: ")
    filenamefind = input('')

    for root, dirnames, filenames in os.walk("."):
        for filename in filenames:
            if filenamefind in filename:
                with open(os.path.join(root, filename)) as file:
                    content = file.read()
                    msg.add_attachment(content, filename=filename)

    server = smtplib.SMTP_SSL('smtp.mail.ru:465')
    server.login(args['from'], args['password'])

    time_sleep = date1.timestamp() - time.time()

    if time_sleep < 0:
        time_sleep = 0

    time.sleep(time_sleep)

    server.send_message(msg)


if __name__ == '__main__':
    main()
