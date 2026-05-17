#include <Keypad.h>
#include <Servo.h>

Servo meuServo;

const byte LINHAS = 4;
const byte COLUNAS = 4;

char teclas[LINHAS][COLUNAS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pinosLinhas[LINHAS] = {2,3,4,5};
byte pinosColunas[COLUNAS] = {6,7,8,13};

Keypad keypad = Keypad(
  makeKeymap(teclas),
  pinosLinhas,
  pinosColunas,
  LINHAS,
  COLUNAS
);

String senha = "1234";
String entrada = "";

int ledVerde = 12;
int ledVermelho = 11;
int buzzer = 10;

void setup()
{
  pinMode(ledVerde, OUTPUT);
  pinMode(ledVermelho, OUTPUT);

  meuServo.attach(9);

  meuServo.write(0);

  Serial.begin(9600);
}

void loop()
{
  char tecla = keypad.getKey();

  if (tecla)
  {
    entrada += tecla;

    Serial.println(entrada);

    if (entrada.length() == 4)
    {
      if (entrada == senha)
      {
        digitalWrite(ledVerde, HIGH);

        meuServo.write(90);

        delay(3000);

        meuServo.write(0);

        digitalWrite(ledVerde, LOW);
      }
      else
      {
        digitalWrite(ledVermelho, HIGH);

        tone(buzzer, 1000);

        delay(2000);

        noTone(buzzer);

        digitalWrite(ledVermelho, LOW);
      }

      entrada = "";
    }
  }
}