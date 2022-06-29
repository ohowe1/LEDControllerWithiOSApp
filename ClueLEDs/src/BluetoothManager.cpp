#include "BluetoothManager.h"

void debugConnectCallback(uint16_t connectHandle) {
    BLEConnection* connection = Bluefruit.Connection(connectHandle);

    char central_name[32] = { 0 };
    connection->getPeerName(central_name, sizeof(central_name));

    Serial.print("Connected to ");
    Serial.println(central_name);
}

void debugDisconnectCallback(uint16_t conn_handle, uint8_t reason)
{
    (void) conn_handle;
    (void) reason;

    Serial.print("Disconnected, reason = 0x"); Serial.println(reason, HEX);
}


void BluetoothManager::setup() {
    Bluefruit.begin();

    Bluefruit.Periph.setConnectCallback(debugConnectCallback);
    Bluefruit.Periph.setDisconnectCallback(debugDisconnectCallback);

    ledService.begin();

    bleDis.setManufacturer("Oliver Howe");
    bleDis.setModel("Bluetooth LED Controller");
    bleDis.begin();

    ledService.begin();

    modeCharacteristic.setProperties(CHR_PROPS_WRITE_WO_RESP | CHR_PROPS_READ);
    modeCharacteristic.setPermission(SECMODE_OPEN, SECMODE_OPEN);
    modeCharacteristic.setMaxLen(9);
    modeCharacteristic.setWriteCallback(modeCallback);
    modeCharacteristic.begin();

    // Adv
    Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
    Bluefruit.Advertising.addTxPower();

    Bluefruit.Advertising.addService(ledService);

    Bluefruit.Advertising.restartOnDisconnect(true);
    Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
    Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
    Bluefruit.Advertising.start(0);
}
