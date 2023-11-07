#if !defined(WSCLIENT_H)
#define WSCLIENT_H

#include <WebSocketsClient.h>
#include <ArduinoJson.h>
#include <Constant.h>

void sendToServer(String payload);
void sendJsonDataToServer(StaticJsonDocument<JSON_LENGTH> data);

typedef std::function<void(char* payload, size_t length)> WebSocketClientMessageHandlerFunctionType;
class WebSocketClientMessageHandler {
   private:
    void onWebSocketConnected(char payload[]);
    void onWebSocketDisconnected();
    WebSocketClientMessageHandlerFunctionType _msgHandler;
    void handleWebSocketEventWithCallback(WStype_t type, uint8_t* payload, size_t length);

   public:
    WebSocketClientMessageHandler(WebSocketClientMessageHandlerFunctionType msgHandler);
    WebSocketsClient::WebSocketClientEvent getHandler();
};

void setupWebSocket(IPAddress address, unsigned int port, WebSocketClientMessageHandlerFunctionType handler);

#endif  // WSCLIENT_H
