from chatterbot import ChatBot
chatbot = ChatBot('Тесла Бот', read_only=False)

def get_response(body):
	'''
	Get response from
	neural network
	'''
	return chatbot.get_response(body)