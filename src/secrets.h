#include <pgmspace.h>
 
#define SECRET
 
const char WIFI_SSID[] = "brisa-2702988";               //TAMIM2.4G
const char WIFI_PASSWORD[] = "o5du40iw";           //0544287380
 
#define THINGNAME "pool-green2b"
 
int8_t TIME_ZONE = -3; //NYC(USA): -5 UTC
 
const char MQTT_HOST[] = "a33yv9okseqbmj-ats.iot.us-east-1.amazonaws.com";  //endpoint AWS
 
 
static const char cacert[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
 MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";
 
 
// Copy contents from XXXXXXXX-certificate.pem.crt here ▼
static const char client_cert[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
 MIIDWTCCAkGgAwIBAgIUDhlTSPcE66kXensMFpWrEu8nW6gwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIzMDgwMjIwMDcz
NloXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANj20RvcbbC0BfuSIeGo
IWrkaBIqyVi7WcMgBFK6n5tAFXTDYkWXp6MJckA36sr5QF7rUwRGSGcBQwBt7zwc
r4PKjr14gClqbAb9NOaPmIkwutDf6tkJtzDcIa2wMsGGH/DLQw9YaqIUSuj2CDzg
fPG4uc22uJT82Kr16D48Otixk81kIY906KS80mXe3aIJAXO5/cYLgPjC9vZohS6N
miqe0VHbIN0zYgrTwjN2hSpLeIyuXDaWxbI4NYmYwzaO7cx2C0lkk5vZZJ4WOU72
ZhiNX6am+jPVdQX8QFzFtXNt2qcsI7yBs8ue8pzGQ5Caxz36Ogse9jmd2MFfzj0H
bc0CAwEAAaNgMF4wHwYDVR0jBBgwFoAUGQMfRB9FTPprEmBabwXQYQtEkjMwHQYD
VR0OBBYEFC3hJtH5uiPHBqEbex/EdrnKxkM+MAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBmWybz9A+JdNX16l/hEReCqd4y
4U2VWS09E1Tm4TVKOYMWTmh51ftsfkDETK5MhqECsXfYEvBypJXzZRj7fG+sdqZN
ash4bQnKUz4Dc3fNxqSL9N5E0viauF3FJf+AcaHPQZGDUuZK6UtqXdJHL/SS32Zk
bSYSMJsZ4mv5pj5j8ASVYzn5U/KxyOVIvfZ+RlhZjnT2XReCGWxpECU8tik5ldBq
guUsk9bfE+JcQaU8PtxEh3FHNJx1ukpyRk1I9KQJ0UXzNVHgT6NFLtXW7XpViGX1
oKZIr2weMG1GJrZMISaQnz8aAiBTdeH5lRmkHuQkBwpz8Nhr/H3kK21RigrL
-----END CERTIFICATE-----
 
)KEY";
 
 
// Copy contents from  XXXXXXXX-private.pem.key here ▼
static const char privkey[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
 MIIEpAIBAAKCAQEA2PbRG9xtsLQF+5Ih4aghauRoEirJWLtZwyAEUrqfm0AVdMNi
RZenowlyQDfqyvlAXutTBEZIZwFDAG3vPByvg8qOvXiAKWpsBv005o+YiTC60N/q
2Qm3MNwhrbAywYYf8MtDD1hqohRK6PYIPOB88bi5zba4lPzYqvXoPjw62LGTzWQh
j3TopLzSZd7dogkBc7n9xguA+ML29miFLo2aKp7RUdsg3TNiCtPCM3aFKkt4jK5c
NpbFsjg1iZjDNo7tzHYLSWSTm9lknhY5TvZmGI1fpqb6M9V1BfxAXMW1c23apywj
vIGzy57ynMZDkJrHPfo6Cx72OZ3YwV/OPQdtzQIDAQABAoIBAAr5eRxSqw28HW1b
N/GFIqOYiBcbKPIfD+xJy04v+HDO7gbo9yiUAjvB95B+A5dewj3K43kc4P6s1qnH
5ckBnnMpJM06sijmJC66Uhmze8C8wUZdfTCbSDPlfqKdfgPB+A2jCnJVQ5eNNTjR
cRs7M7a6ZFOegXmvzHnhVG0JeOSLBxpGOhUXrI16gWhvpR2cEsDi+b5STJrZcz7X
qBPxIlG/+ISUTHFs8B/QNoSJ7gwPx5h2aRcjt7ZOb7U2WMrsvIyqksIarvjpjVmF
JggkfM/K2u7qtoWaIWTX2aLAS3Z6+yrGQwUB7R5LgwDaefQK6V4PwkQfUvDGEkTR
DRTd0QECgYEA692sygPXguCzzEk1Ij/i0jgM7W5d0zRkMD/gYg8CyNJPwonzTquD
lPsnzu/kBei5uIX+wBK9qZlUac0fLnYJU53jyPeSXhkdmCFQihPgTVqr/38Q+E4b
K1e10wBnWx7K5sYrOus4JrXmPK3OsN7HmvC6TPPFvjUZVtA4cXo3VkECgYEA63wV
1makm1kTEmUsRsEe+Xzf6AIcMWx79bhkivG7S3I74qSgxcg+2yKklp0KiUvGwLPS
yB2bkrZqtNPeqvjHISPAGQd/L8ACcG4Pn4gd0pmcR9iwifFqXEtBD8uT2mL3Ty1s
RIoq4heafiYlThQ4OoNf3zMuWq8bK3V+BDDJ7I0CgYEAi6pVAb5qo+YYsXP8EY7Q
6fgkt4dt6X2RgfyhCo+m73GRpzl2qHPpU5OxC9mDJXicWMaHhgbS5hWUJZ4/w4xD
k47f7gWjVzL6EjZP8aM5Y7S4Om9shgwCDJVAZnRLv2opbaOUv6u/MTTu46lrxdH1
UisPtjd3NV1N5tkfQxrCn8ECgYADCjEF+YE6eCXk4OV3bFrIAbKqPgy7HpljDKRP
nts6GBlpzZI9u14EWighwZk3OIEyT5/y8V7mv/AUsX94WYnIhbufFxevOB1P8jvF
ZW5tH4qC6ussfK9Qza/jUk9wTELBBOcW42m2TXOzGS72GRC4wKVmLjT0+rmxD+02
hKK2qQKBgQDadQSbnceBEq1AqcZ2evG7f2bcldIeywWVSf5qjjzEDZAvNDYVFQ2n
O6KA1cjXd7BtLrvVoLQhqMVtPBHNcx25az8upqu7HO0g2sqP7ghcxlFhsuERVP3Z
T/MB71hp8lz5UjQkOEuJR/ysYZvE+9iQa9DnAUcLaQENZERaTrTLvg==
-----END RSA PRIVATE KEY-----
 
)KEY";