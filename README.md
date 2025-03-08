# Arg Parser
> C dilinde, komut satırı argümanlarını daha etkili bir şekilde yönetmek için geliştirilmiş bir kütüphane.

## Açıklama
Sunduğu özellikler:
- **Flag Yönetimi**: Bayrak (flag) parametrelerini işleme ve yönetme.
- **Opsiyonel ve Zorunlu Seçenekler**: Hem opsiyonel hem de zorunlu seçenekleri destekler.
- **Varsayılan Değerler**: Seçenekler için varsayılan değer atama imkanı sağlar.
- **Değer Validasyonu**: Seçeneklere girilen değerlerin doğruluğunu kontrol eder.
- **Yardım Menüsü**: Kullanıcıya komut satırı argümanları hakkında bilgi sunar ve nasıl kullanılacağını gösterir.

---
Örnek program çıktısı 1:
```bash
> ./test
option --zorluk: is require.
```
---
Örnek program çıktısı 2:
```bash
> ./test --genislik metin -h deneme --zorluk IMKANSIZ
Type Error: option --genislik expects an integer. You provided 'metin'.
Type Error: option --hiz expects an double. You provided 'deneme'.
Type Error: option --zorluk expects an ['KOLAY', 'ORTA', 'ZOR']. You provided 'IMKANSIZ'.
```
---
Örnek program çıktısı 3:
```bash
> ./test --help
-?, --help               	yardim ekrani
-m, --mod                	modu degistirir
-g, --genislik <value>   	oyun alaninin genisligini belirler
-y, --yukseklik <value>  	oyun alaninin yuksekligini belirler
-h, --hiz <value>        	oyunun hizini belirler
-t, --test <value>       	test amaclidir
-z, --zorluk <value>    *	oyunun zorlugunu belirler (KOLAY, ORTA, ZOR)
```
---

## İçindekiler
<ol>
	<li>
		<a href="#başlangıç">Başlangıç</a>
		<ul>
			<li><a href="#bağımlılıklar">Bağımlılıklar</a></li>
			<li><a href="#kurulum">Kurulum</a></li>
			<li><a href="#yapılandırma">Yapılandırma</a></li>
			<li><a href="#derleme">Derleme</a></li>
			<li><a href="#çalıştırma">Çalıştırma</a></li>
		</ul>
	</li>
	<li><a href="#dizin-yapısı">Dizin Yapısı</a></li>
	<li><a href="#kullanım">Kullanım</a></li>
	<li><a href="#lisans">Lisans</a></li>
	<li><a href="#Iletişim">İletişim</a></li>
</ol>

## Başlangıç
### Bağımlılıklar
Proje aşağıdaki işletim sistemlerinde test edilmiştir:
- **Debian**

Projenin düzgün çalışabilmesi için aşağıdaki yazılımların sisteminizde kurulu olması gerekir:
- **C Derleyicisi** (GCC, Clang vb.)
- **Make** (Makefile kullanarak derlemek için)
- **Docker** (Docker kullanarak çalıştırmak için)

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

### Kurulum
1. Bu repository'yi kendi bilgisayarınıza klonlayın:
	```bash
	git clone https://github.com/seymenkonuk/arg_parser.git
	```

2. Projeye gidin:
	```bash
	cd arg_parser
	```

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

### Yapılandırma
Yapılandırılacak bir şey yok!

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

### Derleme

Kütüphane, **Makefile** üzerinden kolayca derlenebilir ve linklenebilir.

- **Projeyi derlemek için**:

	```bash
	make
	```

- **Projeyi temizlemek için**:

	```bash
	make clean
	```

Makefile, kütüphanenizi derleyecek ve `bin/libarg_parser.a` statik kütüphanesini oluşturacaktır.

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

### Çalıştırma
Kütüphaneyi kullanan basit bir programı (`test/test.c`) **Docker** üzerinden çalıştırabilirsiniz:
1. Make ve Docker'ı kurunuz.
2. Aşağıdaki komutu çalıştırınız:
	```bash
	make docker
	```

Kütüphaneyi kullanan basit bir programı (`test/test.c`) **Makefile** üzerinden çalıştırabilirsiniz:
1. Make'i kurunuz.
2. Aşağıdaki komutu çalıştırınız:
	```bash
	make test
	```

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

## Dizin Yapısı
```
├── arg_parser/
│   ├── bin/			#Derlenmiş dosyalar
│   ├── obj/			#Obj dosyaları
│   ├── src/			#Kaynak kodlar
│   └── test/			#Projeyi kullanan örnek program
```

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

## Kullanım
Kütüphaneyi kendi C projenizde kullanabilmek için aşağıdaki adımları izleyebilirsiniz:


1. **Kütüphaneyi derleyerek `libarg_parser.a` dosyasını elde edin.**

2. **libarg_parser.a dosyasını `/path/to` dizinine yerleştirin.**

3. **src dizini içindeki bütün .h dosyalarını `/path/to/include/arg_parser` dizinine yerleştirin.**

4. **Kütüphaneyi dahil edin**:

	`#include <arg_parser/arg_parser.h>` satırını, kullanmak istediğiniz C dosyasının başına ekleyin.

5. **Derleme sırasında kütüphaneyi linkleyin**:

	```bash
	gcc -o my_program my_program.c -L/path/to -larg_parser -I/path/to/include
	```

	Burada `/path/to` dizini herhangi bir dizin olabilir.


<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

## Lisans
Bu proje [MIT Lisansı](https://github.com/seymenkonuk/arg_parser/blob/main/LICENSE) ile lisanslanmıştır.

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---

## Iletişim
Proje ile ilgili sorularınız veya önerileriniz için bana ulaşabilirsiniz:

GitHub: https://github.com/seymenkonuk

LinkedIn: https://www.linkedin.com/in/recep-seymen-konuk/

Proje Bağlantısı: [https://github.com/seymenkonuk/arg_parser](https://github.com/seymenkonuk/arg_parser)

<p align="right">(<a href="#arg-parser">back to top</a>)</p>

---
