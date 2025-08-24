# **Stadardit, jotka auttavat kyberturvallisuuden luomisessa**

## a) SFS-EN ISO/IEC 27000:2020:en

- 3.2 *attack*
    - Luvaton ja/tai pahansuopa toimi, jonka tarkoituksena on tuhota, muokata, vioittaa, varastaa tai muutoin tunkeutua ja päästä käsiksi omaisuuteen.
- 3.31 *information security indicent*
    - Yhden tai useamman odottamattoman tietoturvatapahtuman ketju, joka asenteeltaan uhkaa niin yrityksen toiminnan jatkuvuutta että yrityksen sisäistä tietoturvaa.
- 3.56 *requirement*
    - Toimenpide, jonka oletetaan toteutuvan joko oletusarvoisesti tai määrätään suoritettavaksi lain velvoittamana. 
- 3.58 *review*
    - Katsaus siihen, kuinka yksittäisen tai useamman tavoitteen saavuttamiseksi asetettujen toimenpiteiden soveltuvuus sekä tehokkuus sopivat tarpeisiin.
- 3.77 *vulnerability*
    - Joko omaisuuteen tai muuhun toimintaan liittyvä haavoittuvuus, joka on tunnetusti altis yhdelle tai useammalle uhalle.


## b) ISO 24034-1 - 5

### *Standardin ISO/EIC 27034 kokonaisuus ja rakenne*

*ISO/IEC 27034 on kansainvälinen sovellusturvallisuuden standardikokonaisuus, joka koostuu kuudesta osasta:*
- Osa 1 antaa yleissilmäyksen termeihin, prosesseihin ja muihin yleisiin käsitteisiin.
- Osat 2-4 syventyvät tarkemmin itse käytännön toteutuksiin ja toimintaperiaatteisiin.
- Osa 5 puolestaan tarjoaa erityisesti suurille organisaatioille hyödyllisen, standardisoidun rakenteen toimenpiteille ja päivityksiin.
- Osa 6 käy läpi standardin käyttöönottoa sekä niitä prosesseja ja esimerkkejä, joilla sovellusturvallisuuden vaatimukset voidaan täyttää.


## c) Laatuhöpinät 30 ja podcastin väittämät

Kuuntelin Tietoturvallisuus ohjelmistokehityksessä -podcastin 24.8.2025. Podcastissa esitettiin 6 väittämää, jotka ovat listattuina myös nettisivulla. Olen lisännyt omia pohdintojani ja mietteitä seuraaviin väittämiin:

    1. Mikään ohjelmisto ei ole täysin tietoturvallinen.
        - Tietoturva on jatkuvan riskin tila eikä mikään asia voi näin ollen päätyä konseptin ulkopuolelle. Jokainen ohjelmisto tulee sisältämään ainakin jotain inhimillisiä huolimattomuuksia.

    2. Hallinnollinen tietoturva on teknisen tietoturvan onnistumisen edellytys.
        - Hyvä pointti. Ilman selkeitä käytäntöjä, prosesseja tai valvontaa, kontrollit jää väistämättä vajavaisiksi eikä niiden noudattamisesta tai edes toteutumisesta voida olla varmoja.

    3. Automaatiotestaus on ohjelmiston tietoturvan kannalta erittäin tärkeää.
        - Vaikka automaatiotestaus auttaakin löytämään ongelmia ja vähentää inhimillisiä virheitä, vaatii se kaverikseen ja keskusteluun aina mukaan manuaalisen testauksen. Nuo kulkevat sen verran käsi kädessä, että väittämä itsessään jää vähän vaisuksi.

    4. Ohjelmistoa suunniteltaessa voidaan tehdä paljonkin auttamaan käyttäjää toimimaan tietoturvallisesti. Usein nämä toimenpiteet kuitenkin vaikuttavat negatiivisesti käytettävyyteen.
        - Tästä lopputuloksesta on monta käytännön esimerkkiä muun muassa pankkien mobiilisovelluksissa, joista uutisissakin välillä käydään keskustelua puolesta että vastaan. Monivaiheinen tunnistautuminen, salasanavaatimukset ja evästespammi parantavat toki tietoturvaa mutta ärsyttää lähes poikkeuksetta. Valitettava totuus on se, että suurin osa esimerkiksi juurikin pankkihuijauksissa käytetyistä käsikirjoituksista ohittavat näitä tietoturvan nimissä tehtyjä rajoitteita siten, että uhria vain ohjeistetaan toimimaan tietyin tavoin tämän luottaessa puhujaan.

    5. Ohjelmiston tietoturvallisuuden suunnitteluun vaikuttaa paljolti se, kuinka arkaluonteisia tietoja ohjelmistolla on tarkoitus käsitellä.
        - Kuulostaa ihan fiksulta. Jos käsitellään henkilötunnuksia, terveystietoja tai muuta arkaluontoista tietoa niin siihen sovelletaan järeämpiä vaatimuksia kuin esimerkiksi TV-oppaaseen. Riskiperusteinen lähestymistapa on tärkeä osa tietoturvasuunnittelua.

    6. Ohjelmistokehittäjät näkevät omat ohjelmistonsa aina merkittävästi riskialttiimpina, kuin muiden tekemät ohjelmistot.
        - En ole täysin varma mitä mieltä olla. Oma intuitio kertoo, että tässä voi varmasti olla jotain pohjaa, mutta kokemuksen tarrautuessa sitä on ehkä enemmän oltu sokeita juuri omille teoksille. Ulkopuolinen testaus on aina suotavaa kun mahdollista, sillä siinä päästään putkinäöstä eroon ja voidaan keskittyä löytämään täysin uusia tai muuten ajattelemattomia muotoja ohjelmiston toiminnalle.


## d) Riskienhallintasuunnitelma

> Seuraava riskienhallintasuunnitelma perustuu kuvitteelliseen ympäristöön.

### 1. Ympäristön kuvaus

| Nimi | Kuvaus | Versio | Lisätiedot |
| - | - | - | :-: |
| Pääkäyttöjärjestelmä | Windows 11 | 24H2 | - |
| Virtuaalikäyttöjärjestelmä | Debian | 13.0.0 | - |
| Hypervisor | Oracle VirtualBox | 7.2.0 | - |

Tässä riskienhallintasuunnitelmassa kuvaamani ympäristö koostuu opiskeluun tarkoitetusta työasemasta, joka on eristetty muusta käytöstä. Tämä ympäristö pyörii lähtökohtaisesti ainoastaan virtuaalikoneessa, jossa käyttöjärjestelmänä toimii Debian. Työaseman pääkäyttöjärjestelmä on ajantasainen Windows 11. Virtuaalikone käy läpi systemaattiset, täydet uudelleenasennukset sekä puhdistukset erikseen ajoitetuin väliajoin, jotta ympäristöön tallennettu tieto ei ole vaarassa karata ulos.

### 2. Kontrollit
- **Käyttäjähallinta:**
    - Pääkäyttäjä ei ole superuser. Virtuaaliympäristön käytössä on aina väliajoin vaihdettavat, hassunvahvat salasanat, joita ei ole tallennettu tai muutoin otettu ylös mihinkään sisäiseen tai ulkoiseen ympäristöön. Pääympäristössä hyödynnetään salasananhallintaohjelmaa, MFA:ta sekä muita biometrisiä varatoimia.
- **Päivitykset:**
    - Ympäristössä pyörivät käyttöjärjestelmät, ohjelmat, ajurit ja muut päivityksiä edellyttävät tehtävät pidetään ajantasalla siinä määrin missä se on ympäristön kannalta paras vaihtoehto. On hyvä huomioida, vaikka jotakuinkin harvinaista, että jotkin päivitykset voivat aiheuttaa enemmän haittaa kuin hyötyä. Oman ympäristön syvä asiantuntemus sekä aihealueeseen liittyvien uutisten seuraaminen on vahva edellytys päivitysten ymmärtämiselle.
- **Palomuuri, Rajaus ja VPN:**
    - Pääympäristössä on käytössä Windows Defender Antivirus. Virtuaaliympäristössä käytössä on Debian sisäinen palomuuri. Verkkotoimintaa rajataan virtuaaliympäristössä siten, että yhteys ei ole käytössä ilman erillistä tarvetta. Pääympäristö ei aseta erillisiä rajauksia verkkotoimintaan, mutta ei myöskään käytä VPN:ää.
- **Eristys:**
    - Kaikki tiedostot ajetaan ja analysoidaan aina virtuaaliympäristön sisällä ilman verkkoyhteyttä, ellei se ole erikseen vaatimus.
- **Tiedostojen tallennus ja siirto:**
    - Tiedostoja ei siirretä pääympäristöön. Käytössä on kaksi erillistä pilveä, OneDrive ja Google Drive. Ei fyysisiä varmuuskopioita.
- **Puhdistus ja palautus:**
    - Virtuaaliympäristö käy läpi säännölliset puhdistukset ja uudelleenasennukset. Snapshottien käyttö tulee mukaan mahdollisista virhetiloista sekä muista korruptoista palautumiseen.

---

### 3. Riskiarviointitaulukko

| Uhka | Varautuminen | Todennäköisyys | Vakavuus | Suuruus | Suojautuminen |
| :--- | --------------------- | :------------: | :------: | :-----: | ---------------------- |
| Haittaohjelmat | Virtuaaliympäristön suoja | 1 | 3 | <font color="yellow">3</font> | Virtuaaliympäristön jatkuvuus, järjestelmä pidetään ajantasalla ja suoritetaan syviä virtustarkastuksia. |
| Tietojenkalastelu | Valppaus, makro- ja skriptiestot | 2 | 2 | <font color="orange">4</font> | Menetelmien tunteminen ja tunnistaminen, oikeaoppiset jatkotoimet. |
| Fyysinen varkaus | Ei kaapeli- tai kuorilukkoja | 2 | 3 | <font color="red">6</font> | Hankitaan Kensingtonin vehkeet. |

---


# Lähteet
- Arter Oy. 25.10.2021. Laatuhöpinät 30: Tietoturvallisuus ohjelmistokehityksessä. Kuunneltavissa: https://www.arter.fi/podcast/laatulopinat-podcast-tietoturvallisuus-ohjelmistokehityksessa-tarkastele-kokonaisuutta-ja-hyodynna-viitekehykset/. Kuunneltu: 24.8.2025