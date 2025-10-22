# h1 Sniff

## x) Lue ja tiivistä

## a) Linux
Tavoite: *Asenna Debian tai Kali Linux virtuaalikoneeseen.*

1. Kali Linux löytyykin jo asennettuna, joten varmistetaan vielä, että kaikki toimii!

![sniff1](src/sniff1.png)

2. Tulostus toimii ja virtuaalikone näyttää pyörivän. Mennään seuraaviin tehtäviin.

![sniff2](src/sniff2.png)

## b) Ei voi kalastaa
Tavoite: *Osoita, että pystyt katkaisemaan ja palauttamaan virtuaalikoneen Internet-yhteyden.*

1. Testataan ensin yhteyttä kaivamalla Teron kotisivuja. Kysely palauttaa IP-osoitteen, joten yhteys pelaa.

2. Virtuaalikoneen Internet-yhteyden voi sulkea monella eri tapaa, mutta yksinkertaisin vaihtoehto (Kalilla) on viedä hiiri Ethernet-kuvakkeen luokse ja napauttaa yhteys katki.

3. Tämän jälkeen aikaisempi kaivamiskomento ei tuotakaan enää muuta tulosta kuin virheilmoituksia.

4. Internet-yhteyden saa takaisin päälle samasta kohtaa kuin se suljettiin. Testataan ja onneksi näyttää toimivan!

![sniff3](src/sniff3.png)

## c) Wireshark
Tavoite: *Asenna Wireshark. Sieppaa liikennettä Wiresharkilla.*

1. Useimmissa Kali Linuxin asennuksissa tulee Wireshark jo valmiiksi mukana, mutta käydään tämä osio läpi ihan muodollisuuden vuoksi. Wireshark löytyy valmiiksi asennetuissa Kaleissa navigoimalla sovelluslistassa *09 - Discovery -> Wireshark*. Kyllä, sen saa auki myös suoraan komentorivillä.

![sniff4](src/sniff4.png)

2. Liikenteen sieppaamisen voi aloittaa klikkaamalla joko sinistä evää tai näppäinyhdistelmällä *Ctrl+E*.

![sniff5](src/sniff5.png)

3. Liikennettä näyttää olevan runsaasti vaikka mitään ei tekisikään. Surffataan Tero Karvisen kotisivuille ja tarkastellaan siepattua liikennettä sen jälkeen uudestaan.

![sniff6](src/sniff6.png)

## d) Oikeesti TCP/IP
Tavoite: *Osoita TCP/IP-mallin neljä kerrosta yhdestä siepatusta paketista.*

1. Äsken siepatusta liikenteestä kannattaa valita sellainen paketti, joka sisältää myös sovelluskerroksen tietoja. Otetaan omaan esimerkkiin paketti nro. 79.

![sniff7](src/sniff7.png)

2. Tarkastellaan seuraavaksi TCP/IP-mallin neljä kerrosta:

**Peruskerros / Link Layer**

![sniff8](src/sniff8.png)

- Verkkoarkkitehtuurin kellari, jossa paketit liikkuvat saman lähiverkon laitteiden välillä.
- Fyysisessä verkossa kehykset ohjautuvat MAC-osoitteiden perusteella.

**Verkkokerros / Internet Layer**

![sniff9](src/sniff9.png)

- Liikenne kulkee reitittimien kautta eri laitteille IP-osoitteiden avulla.
- Vastuussa paketin pääsemisestä perille.

**Kuljetuskerros / Transport Layer**

![sniff10](src/sniff10.png)

- Liikenne ohjautuu oikealle sovellukselle TCP- tai UDP-porttien kautta.
- Varsinainen tiedonsiirto luodun yhteyden välillä.

**Sovelluskerros / Application Layer**

![sniff11](src/sniff11.png)

- Määrittelee miten tieto tulee esittää kunkin sovelluksen kanssa.
- Esitykseen käytettäviä protokollia ovat muun muassa HTTPS, IRC ja SSH.

## e) Mitäs tuli surffattua? 
Tavoite: *Avaa surfing-secure.pcap. Tutustu siihen pintapuolisesti ja kuvaile, millainen kaappaus on kyseessä.*

1. Hyvä tapa saada pintapuolinen käsitys kaappauksesta on kurkata mitä tiedoston ominaisuuksista löytyy. *Statistics -> File Capture Properties* tai näppäinyhdistelmällä *Ctrl+Alt+Shift+C* tulee esiin paljon infoa.

![sniff12](src/sniff12.png)

2. Näyttäisi olevan aika lyhyt istunto. Yhteensä kaappaus sisältää 283 pakettia ja sen kesto on 7,536 sekuntia. Mitäs seuraavaksi?

3. Protokolleja on useampi: ARP, DNS, QUIC, TCP, TLSv1.2 ja TLSv1.3.

![sniff13](src/sniff13.png)

4. Nopeasti tämä ainakin näyttää siltä, että käyttäjän aloittaessa istuntoa on selaimen aloitussivuna avautunut Googlen hakukenttä (QUIC), jonka jälkeen DNS-kysely Tero Karvisen kotisivuille viittaa varsinaiseen selailun aloittamiseen.

## f) Selain (Vapaaehtoinen)
Tavoite: *Mitä selainta käyttäjä käyttää?*

## g) Verkkokortti surfing-secure.pcap
Tavoite: *Minkä merkkinen verkkokortti käyttäjällä on?*

## h) Weppipalvelin
Tavoite: *Millä weppipalvelimella käyttäjä on surffaillut?*

## i) Analyysi
Tavoite: *Sieppaa pieni määrä omaa liikennettäsi. Analysoi se, eli selitä mahdollisimman perusteellisesti, mitä tapahtuu.*

## Lähteet
- Tero Karvinen 2025. Verkkoon tunkeutuminen ja tiedustelu. Luettavissa: https://terokarvinen.com/verkkoon-tunkeutuminen-ja-tiedustelu
- Tero Karvinen 2025. Wireshark - Getting Started. Luettavissa: https://terokarvinen.com/wireshark-getting-started/
- Tero Karvinen 2025. Network Interface Names on Linux. Luettavissa: https://terokarvinen.com/network-interface-linux/