keywords = {
    'greet': ['hi', 'hello', 'hey', 'good morning', 'good afternoon', 'good evening', 'hi bot'],
    'name': ['what is your name ?', 'what are you ?', 'who are you ?'],
    'thank': ['thanks', 'thank you', 'thank you very much', 'thank you so much'],
    'quit': ['bye', 'good bye', 'exit', 'quit', 'i should go', 'i have to go']
}

responses = {
    'greet': "Hello ! How can I help you ?",
    'name': "I am your chatbot . You can call me Bot :)",
    'thank': "You are welcome :)",
    'quit': "Thank you for contacting . I hope this is not the last time , good bye ..",
    'NA': "I don't quite understand . Could you repeat that more clearly ?"
}

print("\n<< Welcome to My ChatBot >>\n\n")
userName = input("Please , Enter your name : ")
print("Nice to meet you , " + userName + " .\n\nHow can I help you ?\n")

while True:
    request = input(userName + " : ")
    if request.lower() in keywords['quit']:
        print("Bot : " + responses['quit'])
        break
    else:
        response = responses['NA']
        for keyword in keywords:
            if request.lower() in keywords[keyword]:
                response = responses[keyword]
        print("Bot : " + response)
