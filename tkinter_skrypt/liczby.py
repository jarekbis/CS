from tkinter import *

window = Tk()
window.title("Liczby")

def zamiana():
    liczba = txt_liczba.get()
    podstawa = txt_podstawa.get()
    liczba = int(liczba, int(podstawa))
    lbl_wynik["text"] = "Dwójkowo: "+bin(liczba)[2:]+"\nSzesnastkowo: "+hex(liczba)[2:]+"\nDziesietnie: "+str(liczba)

lbl_tytul = Label(master = window, text = "Program do zamiany systemów liczbowych")
lbl_tytul.grid(row = 0, column = 0, padx = 10, pady = 10)

lbl_t1 = Label(master = window, text = "Podaj liczbę")
lbl_t1.grid(row = 1, column = 0, padx = 10, pady = 10)

txt_liczba = Entry(master = window, width = 20)
txt_liczba.grid(row = 2, column = 0, padx = 10, pady = 10)

lbl_t2 = Label(master = window, text = "Podaj podstawę systemu")
lbl_t2.grid(row = 3, column = 0, padx = 10, pady = 10)

txt_podstawa = Entry(master = window, width = 20)
txt_podstawa.grid(row = 4, column = 0, padx = 10, pady = 10)

btn_oblicz = Button(master = window, text = "Oblicz", command = zamiana)
btn_oblicz.grid(row = 5, column = 0, padx = 10, pady = 10)

lbl_wynik = Label(master = window, text = "Wynik obliczeń")
lbl_wynik.grid(row = 6, column = 0, padx = 10, pady = 10)

window.mainloop()
