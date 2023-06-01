import requests

token = '5323225784:AAHmokKvOySqqOOUUpks8N26frA-wLBNf5A'
chat_id = '670724318'
message_file = 'tl'

def send_telegram_message():
    # Читаем текст сообщения из файла
    with open(message_file, 'r') as file:
        message_text = file.read()

    # URL для отправки сообщения в Telegram
    url = f'https://api.telegram.org/bot{token}/sendMessage'

    # Параметры для запроса
    params = {
        'chat_id': chat_id,
        'text': message_text
    }

    # Отправляем запрос
    response = requests.post(url, data=params)
    # Проверяем статус ответа
    if response.status_code == 200:
        print('Сообщение успешно отправлено в Telegram!')
    else:
        print(f'Произошла ошибка: {response.status_code}')
    os.remove(message_file)
    