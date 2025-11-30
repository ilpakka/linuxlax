# h4 NFC ja RFID

## a) RFID.
Tavoite: *Tarkastele käytössäsi olevia RFID-tuotteita ja mieti, miten hyvin olet suojautunut urkinnalta?*

1. RFID-tuotteita on kaikilla varmaan jopa enemmän kuin mitä olettavatkaan. RFID kattaa esimerkiksi NFC-laitteet, joita ovat pankkikortit, kulkulätkät tai vaikka epähuomiossa housuihin kiinni jäänyt hälytin. Muita kategorioita kuten MIFARE:a on joiltain vielä löytyvät vanhat HSL-matkakortit. Mmyös modernien passien RFID-sirut sisältävät runsaasti henkilökohtaista dataa.

2. Tässä tulee vähän jo OPSEC viereen istumaan, mutta urkinnalta olen mahdollisesti suojautunut poistamalla käyttämättömät RFID-teknologiat, kuten vaikka älypuhelimen lähimaksut. En kanna mukanani RFID-laitteita niitä tarvitsematta ja mahdollisen urkinnan pinta-ala kutistuu.

## b) APDU.
Tavoite: *Tutustu APDU-komentojen rakenteeseen.*

1. Kävin tutustumassa CardLogixin sivuilta löytyvään artikkeliin, jossa APDU-komennot sekä itse APDU avataan fiksusti auki.

2. APDU (Application Protocol Data Unit) on kortin ja lukijan välinen viestipätkä, jonka komennot koostuvat erilaisista, kahden pääosan lohkoista:

| Pakollinen otsake | Pituus tavuina | Selitys |
| :---------------- | --------------- | ------- |
| CLA | 1 | Komennon tyyppi, kuten "yleinen" |
| INS | 1 | Komennon koodi, esm "write data" |
| P1-P2 | 2 | Parametrit, jotka tarkentavat komentoa | 

| Valinnainen osuus | Pituus tavuina | Selitys |
| :---------------- | --------------- | ------- |
| Lc | 0, 1 tai 3 | Kuinka monta tavua dataa tulee perässä |
| Data Field | <256 | Sisältö |
| Le | 0 - 3 | Vastauksen odotettu koko |

3. APDU:lta löytyy myös vastauksia:

| Vastaus | Pituus tavuina | Selitys |
| ---- | -------------- | ------- |
| Response Data | >Le | Vastauksen odotettu koko |
| SW1-SW2 | 2 | Kertoo tuloksen |

4. APDU:n vastaukset (SW1-SW2) jaetaan kolmeen osaan: *90 00* (onnistunut), *6A 82* (ei löytynyt) sekä *69 82* (estetty).

## c) Uutiset.
Tavoite: *Tutki ja kerro minkä mielenkiintoisen RFID-hakkeriuutisen löysit.*

1. Menin vähän kauemmaksi etsimään uutisia ja vastaan hyppäsi ihan mielenkiintoinen tapaus vuodelta 2008. The Guardianin artikkeli kertoo Radboudin yliopiston tutkijoiden suorittamasta tempauksesta, jossa he mursivat Oyster-kortin käyttämän MIFARE-sirun salauksen ja lisäsivät "saldoa tyhjästä" liikkuakseen vapaasti Lontoon metroilla. Murtaminen oli tutkijoiden mukaan pelottavan helppoa, sillä se vaati ainoastaan kannettavan tietokoneen ja RFID-lukijan. Salauksen murtaminen vei ainoastaan muutaman sekuntin.

2. Tapauksen jälkeen Transport for London vakuutteli, että tässä ei ole suurempaa hätää. Hyökkäys kuitenkin osoitti sen, että sirun käyttämä Crypto1-salausalrogitmi oli vaarallisen haavoittuvainen ja altisti myös muut vastaavat kortit väärinkäytölle. Oysterin käyttö jatkui tästä huolimatta täysin normaalisti.

## Lähteet
- Tero Karvinen 2025. Verkkoon tunkeutuminen ja tiedustelu. Luettavissa: https://terokarvinen.com/verkkoon-tunkeutuminen-ja-tiedustelu
- CardLogix. Application Protocol Data Unit (APDU). Luettavissa: https://www.cardlogix.com/glossary/apdu-application-protocol-data-unit-smart-card/
- The Guardian. Has London's Oyster travelcard system been cracked? Luettavissa: https://www.theguardian.com/technology/2008/jun/26/hitechcrime.oystercards