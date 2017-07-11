# Projekt Chat

Jednoduchý chat v rámci jedné chatovací místnosti.

- Libovolné množství se může připojit k serveru
- Server zajišťuje správné posílání zpráv
    - varianta 0: server posílá všem
    - variatna 1: server umožňuje privátní zprávy
- Server:
    - varianta 0: U Honzy na počítači
    - varianta 1: Dedikovaný server na ESP
- Typické použití/průběh komunikace (mějme X jako klienta):
    - X se připojí
    - server notifikuje ostatní o připojení X
    - server X pošle uvítací zprávu
        - mapování IP adresa -> přezdívku
        - = seznam uživatelů online
    - X nastaví svoji přezdívku
    - Server posílá keep alive zprávy, X je ignoruje
- Formát zprávy pro klienta:
    - `[1 znak přikaz][4 znaky binární IP adresa][data]'\0'`
- Podporované příkazy:
    - c (připojil se) `[přezdívka]`
    - d (odpojil se) `[]`
    - m (posílá zprávu) `[zpráva]`
    - t (píše)
        - co řádek, to IP adresa následovaná jménem
    - w (uvítací zpráva) `[jméno]`