import os
from tkinter import *
from tkinter import ttk 
from currency import Currency 

class Currnecy(object):
    def __int__(self, master):
         frame = Frame(master) #frame to import it to gui
         frame.grid #grid of the gui
         self.currency = Currency()
         self.options = ["EUR", "USD", "CAD", "NZD", "CYN", "AUD", "DKK", "GBP", "JPN" ]

         self.amount_label = Label(root, text = "Amount: ")
         self.amount_label.grid(column = 0, row = 0)
         self.amount_entry = Entry(root) #takes the entry
         self.amount_entry.grid(column = 1, row = 0)

         self.selection_frame = LabelFrame(root, text = "Currencies: ")
         self.selection_frame.grid(column = 0, row = 1, columnspan = 2)
         self.frame_label = Label(self.selection_frame, text="From")
         self.frame_label.grid(column=0, row=0)
         self.to_label = Label(self.selection_frame, text="To: ")#user can select which currency he wants it converted to
         self.to_label.grid(column=1, row=0)#grid for the option above

         self.from_menu = ttk.Combobox(self.selection_frame, values= self.options)
         self.from_menu.grid(column=1, row= 0)
         self.from_menu.current(1)
         self.to_menu = ttk.Combobox(self.selection_frame, values=self.options)
         self.to_menu.grid(column=1, row=1)
         self.to_menu.current(1)

         self.result_label = Label(root, text="")
         self.result_label.grid(column=0, row=2, columnspan=2)
         self.convert_button = Button(root, text= "Convert!", command=self.converter)
         self.convert_button.grid(column=0, row=3, columnspan=2)

    def converter(self):
        try:
            currency_result = round(self.currency.converter(float(self.amount_entry.get()), self.from_menu.get(), self.to_menu.get(), 2))#getting the amount entry
            self.result_label.configure(text=f"{self.result_label}{self.to_menu.get()}")#whatever is returned here it will be put into the f string above 
        except ValueError:
            self.result_label.configure(text="This is not a number")#this is for the user if he puts in a letter instead of a number

    if __name__ == "__main__":
        os.chdir(os.path.dirname(os.path.realpath(__file__)))
        root = Tk()
        root.title("Currency Converter")
        Currency(root)
        root.mainloop()
