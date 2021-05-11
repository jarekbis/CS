from tkinter import *

window = Tk()
window.title("Szyfrator Viginere")

def viginere():
    w = txt_jawny.get()
    h = txt_klucz.get()
    pom = ''
    lenh=len(h)
    wiadomosc = w
    for i in range(len(wiadomosc)):
        k = ord(h[i % lenh]) - ord('A')
        litera = wiadomosc[i]
        if 'A'<=litera<='Z' :
            litera = (ord(litera)-ord('A') + k) % 26
            litera = chr(litera+ord('A'))
        pom += litera
    lbl_wynik["text"] = pom

lbl_tabela = Label(window, font = 'TkFixedFont', bg = 'white')
tekst_tabeli = ['\n']
for a in range(26):
    for b in range(26):
        tekst_tabeli.append(chr(ord('A')+(a+b)%26)+' ')
    tekst_tabeli.append('\n')
tekst_tabeli="".join(tekst_tabeli)
lbl_tabela['text'] = tekst_tabeli

lbl_tabela.grid(row=0, column = 1, rowspan=5)

lbl_t1 = Label(window, text = "Wiadomość do szyfrowania")
lbl_t1.grid(row = 0, column = 0, sticky = 'S')

txt_jawny = Entry(window)
txt_jawny.grid(row = 1, column = 0)


lbl_t2 = Label(window, text = "Klucz")
lbl_t2.grid(row = 2, column = 0, sticky = 'S')

txt_klucz = Entry(window)
txt_klucz.grid(row = 3, column = 0)

lbl_wynik = Label(window, text = "")
lbl_wynik.grid(row=4, column=0, sticky = 'S')

btn_szyfruj = Button(master = window, text = "Szyfruj", command = viginere)
btn_szyfruj.grid(row = 5, column = 0, columnspan=2, pady=10)

window.mainloop()

