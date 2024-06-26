#include <Arduino.h>

// 'supabase url' dan 'anon key' yang didapat dari laman supabase
const String url = "https://bsrdzvhhtaqykofwtocw.supabase.co";
const String apikey = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJpc3MiOiJzdXBhYmFzZSIsInJlZiI6ImJzcmR6dmhodGFxeWtvZnd0b2N3Iiwicm9sZSI6ImFub24iLCJpYXQiOjE3MTg4OTc5MTMsImV4cCI6MjAzNDQ3MzkxM30.bhN4-JBYTUIPsz99j5p6RNapjYxtW-0Mr3YE4Or5n0g";
const String table = "data";

// masukkan nama wifi dan password yang ingin disambungkan
const char *ssid = "Galaxy A71b946";
const char *password = "123456789";

unsigned long timeDelay = 300000; // berapa milidetik jeda tiap pengiriman data (5 menit)
bool isSend = true;

// tambahkan/kurangi sensor sesuai kebutuhan anda
const int jumlahSensor = 6;
// nama sensor untuk ditampilkan pada web, isi pada array harus sesuai jumlah sensor
String name[jumlahSensor] = {"Suhu1", "Suhu2", "Kelembapan1", "Kelembapan2", "Berat1", "Berat2"};
// tipe sensor untuk ikon web, isi pada array harus sesuai jumlah sensor
String type[jumlahSensor] = {"temperature", "temperature", "relativeHumidity", "relativeHumidity", "weight", "weight"};
// satuan data sensor untuk tampilan web, isi pada array harus sesuai jumlah sensor
String unit[jumlahSensor] = {"°C", "°C", "%", "%", "kg", "kg"};
// nilai data sensor
float value[jumlahSensor];

String makeJSON(float value[])
{
    String httpReqData = "";
    StaticJsonDocument<1024> doc;
    doc["refresh"] = timeDelay;
    JsonArray data = doc.createNestedArray("data");

    for (int i = 0; i < jumlahSensor; i++)
    {
        JsonObject sensor = data.createNestedObject();
        sensor["name"] = name[i];
        sensor["type"] = type[i];
        sensor["unit"] = unit[i];
        if (i==4){
            if (value[i]==0){
                sensor["value"] = "Mati";
            }
            else {
                sensor["value"] = "Nyala";
            }
        } 
        else {
            sensor["value"] = value[i];
        }
    }
    serializeJson(doc, httpReqData);
    
    return httpReqData;
}
