from flask import Flask, request, jsonify
import os

app = Flask(__name__)

@app.route('/')
def serve_html():
    # Serve the HTML file from the same directory as the app.py
    return app.send_static_file('remote.html')

@app.route('/forward_data', methods=['POST'])
def forward_data():
    # Get data from the request
    data = request.json

    # Define the target OM2M server and port
    om2m_server = 'http://127.0.0.1'
    om2m_port = 5089

    # Forward the data to the OM2M server
    # You can customize this part to fit your specific OM2M request format
    # For example, you can use the requests library to send the data to the OM2M server
    # Example: requests.post(f'{om2m_server}:{om2m_port}/your_target_endpoint', json=data)

    return jsonify({'message': 'Data forwarded to OM2M server'})

if __name__ == '__main__':
    # Serve the HTML file from the "static" folder
    app.static_folder = os.path.abspath("static")
    app.run(host='127.0.0.1', port=5000)
