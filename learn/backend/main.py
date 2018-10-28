from flask import Flask
from flask import jsonify
from flask import make_response
from flask import request
from chatterbot import ChatBot

chatbot = ChatBot('Тесла Бот', read_only=False)
app = Flask(__name__)

@app.route('/api_v1/learning/get_responce', methods=['GET'])
def info():
	return jsonify({'body' : chatbot.get_response(request.args['body'])})

if __name__ == '__main__':
    app.run(host='localhost', port=5000, debug=True)
