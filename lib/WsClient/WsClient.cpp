#include <WsClient.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <MessageHandler.h>
#include <Utils.h>

WebSocketsClient webSocket;

void sendToServer(String payload) {
    webSocket.sendTXT(payload.c_str());
}

void sendJsonDataToServer(StaticJsonDocument<JSON_LENGTH> data) {
    auto payload = SerializeJSONData2String(data);
    sendToServer(payload);
}

void WebSocketClientMessageHandler::onWebSocketConnected(char payload[]) {
    Serial.print("[WSc] Connected to url: ");
    Serial.println(payload);

    webSocket.sendTXT("Connected");
}

void WebSocketClientMessageHandler::onWebSocketDisconnected() {
    Serial.println("[WSc] Disconnected!\n");
}

WebSocketClientMessageHandler::WebSocketClientMessageHandler(WebSocketClientMessageHandlerFunctionType msgHandler) {
    _msgHandler = msgHandler;
}

WebSocketsClient::WebSocketClientEvent WebSocketClientMessageHandler::getHandler() {
    return [&](WStype_t type, uint8_t *payload, size_t length) {
        switch (type) {
            case WStype_DISCONNECTED:
                onWebSocketDisconnected();
                break;
            case WStype_CONNECTED:
                onWebSocketConnected((char *)payload);
                break;
            case WStype_TEXT:
                Serial.print("[WSc] get text: ");
                Serial.println((char *)payload);
                _msgHandler((char *)payload, length);
                break;
            case WStype_BIN:
                Serial.print("[WSc] get binary length: ");
                Serial.println(length);
                // hexdump(payload, length);

                // send data to server
                // webSocket.sendBIN(payload, length);
                break;
            default:
                Serial.println(type);
        }
    };
}

void setupWebSocket(IPAddress address, unsigned int port, WebSocketClientMessageHandlerFunctionType callback) {
    webSocket.begin(address, port);
    WebSocketClientMessageHandler handler(callback);
    webSocket.onEvent(handler.getHandler());
}
