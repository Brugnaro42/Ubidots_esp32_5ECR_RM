# esp32_5ECR_RM

![GitHub issues](https://img.shields.io/github/issues/Brugnaro42/Ubidots_esp32_5ECR_RM)
![GitHub forks](https://img.shields.io/github/forks/Brugnaro42/Ubidots_esp32_5ECR_RM)
![GitHub stars](https://img.shields.io/github/stars/Brugnaro42/Ubidots_esp32_5ECR_RM)

> Repositório para armazenarmos os códigos fontes relativos ao trabalho de IoT, que consiste na interação entre a placa ESP32 e o broken provido pelo Ubidots.

## Ajustes e melhorias
- [x] Testar pisca-pisca com o LED embarcado do ESP32;
- [x] Realizar as leituras do M6050;
- [x] Converter as leituras do M6050 de rad para graus;
- [x] Enviar informações para o UbiDots;
- [x] Fazer o DigitalWrite do Buzzer;
- [ ] Receber informações do UbiDots (Subscribe);
  - [x] Para o LED;
  - [ ] Para o Buzzer;
 

## ☕ Usando o projeto

Para usar os recursos, siga estas etapas:
  - Preencha o arquivo `confidentialStuffExample.h` com as especificações descritas;
  - Renomeie o arquivo `confidentialStuffExample.h` para `confidentialStuff.h`;
  - Copie e cole o arquivo para todas as subpastas dentro da pasta `ubidots`;
  - Depois disso, basta compilar para ver se tudo está configurado, se não reveja os passos descritos anteriormente;

## 📫 Contribuindo para <nome_do_projeto>
Para contribuir com o nosso projeto, siga estas etapas:

1. Bifurque este repositório.
2. Crie um branch: `git checkout -b <nome_branch>`.
3. Faça suas alterações e confirme-as: `git commit -m '<mensagem_commit>'`
4. Envie para o branch original: `git push origin <nome_do_projeto> / <local>`
5. Crie a solicitação de pull.
