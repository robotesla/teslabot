from mind.dialog import get_response

while True:
    user_message = input('> ')
    print(get_response(user_message))