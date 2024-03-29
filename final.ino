

#include "CTBot.h"
CTBot myBot;

String ssid = "no internet";     // REPLACE mySSID WITH YOUR WIFI SSID
String pass = "nomeansno"; // REPLACE myPassword YOUR WIFI PASSWORD, IF ANY
String token = "977896158:AAEDaxYUZ3-AX5K5G0G3ETnOOM7zDGSBSXQ";   // REPLACE myToken WITH YOUR TELEGRAM BOT TOKEN
uint8_t led = BUILTIN_LED;            // the onboard ESP8266 LED.    
                            // If you have a NodeMCU you can use the BUILTIN_LED pin
                            // (replace 2 with BUILTIN_LED)							

void setup() {
	// initialize the Serial
	Serial.begin(115200);
	Serial.println("Starting TelegramBot...");

	// connect the ESP8266 to the desired access point
	myBot.wifiConnect(ssid, pass);

	// set the telegram bot token
	myBot.setTelegramToken(token);

	// check if all things are ok
	if (myBot.testConnection())
		Serial.println("\ntestConnection OK");
	else
		Serial.println("\ntestConnection NOK");

	// set the pin connected to the LED to act as output pin
	pinMode(D3, OUTPUT);
	digitalWrite(D3, HIGH); // turn off the led (inverted logic!)
  pinMode(D1,OUTPUT);
  digitalWrite(D1, HIGH); // turn off motor

}

void loop() {
	// a variable to store telegram message data
	TBMessage msg;

	// if there is an incoming message...
	if (myBot.getNewMessage(msg)) {

		if (msg.text.equalsIgnoreCase("LIGHT ON")) {              // if the received message is "LIGHT ON"...
			digitalWrite(D3, LOW);                               // turn on the LED (inverted logic!)
			myBot.sendMessage(msg.sender.id, "Light is now ON");  // notify the sender
		}
		else if (msg.text.equalsIgnoreCase("LIGHT OFF")) {        // if the received message is "LIGHT OFF"...
			digitalWrite(D3, HIGH);                              // turn off the led (inverted logic!)
			myBot.sendMessage(msg.sender.id, "Light is now OFF"); // notify the sender
		}
    else if (msg.text.equalsIgnoreCase("FAN ON")) {              // if the received message is "FAN ON"...
      digitalWrite(D1, LOW);                               // turn on the FAN (inverted logic!)
      myBot.sendMessage(msg.sender.id, "FAN is now ON");
    }
    else if (msg.text.equalsIgnoreCase("FAN OFF")) {        // if the received message is "FAN OFF"...
      digitalWrite(D1, HIGH);                              // turn off the FAN (inverted logic!)
      myBot.sendMessage(msg.sender.id, "FAN is now OFF"); // notify the sender
    }
    else {                                                    // otherwise...
			// generate the message for the sender
			String reply;
			reply = (String)"Welcome " + msg.sender.username + (String)". Try LIGHT ON or LIGHT OFF.";
			myBot.sendMessage(msg.sender.id, reply);             // and send it
		}
	}
	// wait 500 milliseconds
	delay(500);
}
