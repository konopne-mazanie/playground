import Tkinter as tk
from ttk import *
import platform
from mp import power, workprec, workdps, sin, asin, cos, acos, tan, atan, isinf
from math import degrees, radians

iserr=False
mem=[]

class clbutton(Button):
	def __init__(self, txt, com, wdth, rw, clm, ism=False):
		Button.__init__(self, okno)
		self.master=okno
		self["text"]=txt
		self["command"]=eval("lambda : " + com)
		self["width"]=wdth
		if ism==True:
			self["style"]="M.TButton"
		self.grid(row=rw, column=clm,padx=2,pady=2)

def do(var,md):
	if var!="":
		if var=="about":
			return("# By Peter Uhrecky Version: 1.00 Written in Python 2.7      ")
		memf(var)

		var=var.replace("fact","factorial")
		var=var.replace("pow","power")
	
		if md=="DEG":
			for j in ["asin","atan","acos","sin","cos","tan"]:
				var=var.replace(j+"(", "chmp("+j+",")
	
		var="from __future__ import division;from mp import *;from calc import root,chmp;mp.dps=25;mp.prec=83.25;a="+var
		ns = {}
	try:
		if var=="":
			raise TypeError
		code = compile(var, "script", "exec")	
		exec code in ns
		var=ns['a']
		try:
			if isinf(float(var)):
				raise OverflowError
		except TypeError:
			raise ValueError
	except ZeroDivisionError:
		var="#0 Zero division"
	except ValueError:
		var="#1 Bad function value"
	except SyntaxError:
		var="#2 Bad syntax"
	except TypeError:
		var="#3 Bad type of input"
	except OverflowError:
		var="#4 Too big number"
	except NameError:
		var="#3 Bad type of input"
	return(var)

def root(x,y):
	with workdps(10):
		x=float(x)
		y=str(y)
		if not "." in y:
			y=y+".0"
		return(power(x,1/float(y)))

def chmp(l,num):
	if l==sin:
		num=radians(num)
		return(sin(num))
	elif l==asin:
		return(degrees(asin(num)))
	elif l==cos:
		num=radians(num)
		return(cos(num))
	elif l==acos:
		return(degrees(acos(num)))
	elif l==tan:
		num=radians(num)
		return(tan(num))
	elif l==atan:
		return(degrees(atan(num)))

def prnt(x):
	if e.selection_present():
		etext=e.get()
		esel=e.selection_get()

		if e.index("anchor") < e.index("insert"):
			etbef=etext[:e.index("anchor")]
			esle=e.index("insert")
			etaft=etext[esle:]
		else:
			etbef=etext[:e.index("insert")]
			esle=e.index("anchor")
			etaft=etext[esle:]

		if x in ["asin(","atan(","acos(","sin(","cos(","tan(", "sqrt(", "fact(", "-(", "log10(", "ln("]:
			e.delete(0,"end")
			e.insert(0,etbef+x+esel+")"+etaft)
			e.icursor(esle+len(x)+1)
		elif x == "pow(,2)":
			e.delete(0,"end")
			e.insert(0,etbef+"pow("+esel+",2)"+etaft)
			e.icursor(esle+7)
		elif x == "pow(,)":
			e.delete(0,"end")
			e.insert(0,etbef+"pow("+esel+",)"+etaft)
			e.icursor(esle+5)
		elif x == "log(,)":
			e.delete(0,"end")
			e.insert(0,etbef+"log("+esel+",)"+etaft)
			e.icursor(esle+5)
		elif x == "root(,)":
			e.delete(0,"end")
			e.insert(0,etbef+"root("+esel+",)"+etaft)
			e.icursor(esle+6)			
		elif x == "pow(,-1)":
			e.delete(0,"end")
			e.insert(0,etbef+"pow("+esel+",-1)"+etaft)
			e.icursor(esle+8)
		

	else:
		e.insert("insert", x)
		if x == "pow(,2)":
			e.icursor(e.index("insert")-3)
		elif x == "pow(,)" or x == "log(,)" or x == "root(,)":
			e.icursor(e.index("insert")-2)
		elif x == "pow(,-1)":
			e.icursor(e.index("insert")-4)

	e.xview(e.index("insert"))
	e.focus_set()

def reslt(res):
	global iserr
	e.delete(0,"end")
	if "#" in str(res):
		e.insert(0,res+"! Press cl to continue...")
		e.config(state="readonly")
		bdeg.config(state="disabled")
		bcount.config(state="disabled")
		bremv.config(state="disabled")
		bmem.config(state="disabled")
		lb.config(foreground="red")
		md.set("ERR")
		iserr=True
	else:
		e.insert(0,res)
		e.focus_set()

def clf():
	global iserr
	if iserr == True:
		e.config(state="normal")
		bdeg.config(state="normal")
		bcount.config(state="normal")
		bremv.config(state="normal")
		bmem.config(state="normal")
		lb.config(foreground="green")
		md.set("RAD")
		iserr=False

	e.delete(0,"end")
	e.focus_set()

def chmod():
	if md.get()=="RAD":
		md.set("DEG")
	else:
		md.set("RAD")

	if e.get()!="":
		try:
			s=float(e.get())
			e.delete(0,"end")
			if md.get()=="RAD":
				e.insert(0,str(radians(s)))
			else:
				e.insert(0,str(degrees(s)))
    		except ValueError:
			pass        	

	e.focus_set()

def memf(item):
	if not item in mem:
		if len(mem)>4:
			mem.pop(0)
			menu.delete(0,0)
		menu.add_command(label=item,  command=lambda : menuf(item))
		mem.append(item)

def menuf(item):
	e.delete(0,"end")
	e.insert(0,item)

def remvf():
	if e.selection_present():
		etext=e.get()
		esel=e.selection_get()

		if e.index("anchor") < e.index("insert"):
			etbef=etext[:e.index("anchor")]
			esle=e.index("insert")
			etaft=etext[esle:]
		else:
			etbef=etext[:e.index("insert")]
			esle=e.index("anchor")
			etaft=etext[esle:]

		e.delete(0,"end")
		e.insert(0,etbef+etaft)
		e.icursor(esle-len(esel))
		e.xview(e.index("insert"))
		e.focus_set()
	else:
		e.delete(e.index("insert")-1,e.index("insert"))
		e.focus_set()

def main():
	global md, e, lb, bremv, bcount, bdeg, bmem, menu, okno
	okno= tk.Tk()
	okno.style = Style()
	okno.wm_title("Calc")
	okno.resizable(0,0)
	ico = tk.Image("photo", file="icon.gif")
	okno.tk.call('wm','iconphoto',okno._w,ico)
	md= tk.StringVar()
	bmem = Menubutton(okno, text="m", width=4, style="M.TButton")
	
	if platform.system()=="Linux":
		okno.configure(background="black")
		Style().configure("TButton", relief="flat", background="black", foreground="white", padding=12, font=("Times", 15))
		Style().configure("M.TButton", font=("Times", 15, "bold"))
		Style().map("TButton", background=[("active","green")])
		e= tk.Entry(okno, width=46, font=("Times", 20), borderwidth=0, background="black", foreground="white", highlightbackground="black", insertbackground="white", selectbackground="#ccc", selectforeground="black", readonlybackground="black")
		menu = tk.Menu(bmem, background="black", activebackground="green", activeforeground="white", foreground="white", font=("Times", 15), relief="raised", tearoff=0)
		lb = tk.Label(okno, textvariable=md, background="black", foreground="green", font=("Times", 20), relief="flat", takefocus="false")
	else:
		okno.configure(background='#F0F0F0')
		Style().configure("TButton", relief="flat", padding=12, font=("Arial", 15))
		Style().configure("M.TButton", font=("Arial", 15, "bold"))
		e= tk.Entry(okno, width=46, font=("Times", 20), borderwidth=0, background="#F0F0F0", foreground="black", highlightbackground="black", insertbackground="black", selectbackground="#ccc", selectforeground="black", readonlybackground="#F0F0F0")
		menu = tk.Menu(bmem, font=("Times", 15), tearoff=0)
		lb = tk.Label(okno, textvariable=md, foreground="green", font=("Times", 20), relief="flat", takefocus="false")

	md.set("RAD")
	bmem.config(menu=menu)
	bmem.grid(row=4, column=5,padx=2,pady=2)

	e.grid(row=0, column=0,columnspan=9,padx=2,pady=2)
	lb.grid(row=0, column=9,padx=2,pady=2)

	b1 = clbutton("1","""prnt("1")""",2,1,0)
	b2 = clbutton("2","""prnt("2")""",2,1,1)
	b3 = clbutton("3","""prnt("3")""",2,1,2)
	b4 = clbutton("4","""prnt("4")""",2,2,0)
	b5 = clbutton("5","""prnt("5")""",2,2,1)
	b6 = clbutton("6","""prnt("6")""",2,2,2)
	b7 = clbutton("7","""prnt("7")""",2,3,0)
	b8 = clbutton("8","""prnt("8")""",2,3,1)
	b9 = clbutton("9","""prnt("9")""",2,3,2)
	b0 = clbutton("0","""prnt("0")""",2,4,0)
	bc = clbutton(".","""prnt(".")""",2,4,2)

	bplus = clbutton("+","""prnt("+")""",4,1,3)
	bmin = clbutton("-","""prnt("-")""",4,2,3)
	bexp = clbutton("*","""prnt("*")""",4,1,4)
	bdec = clbutton("/","""prnt("/")""",4,2,4)
	bz1 = clbutton("(","""prnt("(")""",4,1,5)
	bz2 = clbutton(")","""prnt(")")""",4,1,6)
	bmo2 = clbutton(chr(94)+"2","""prnt("pow(,2)")""",4,2,5)
	bdod2 = clbutton("sqrt","""prnt("sqrt(")""",4,2,6)
	bsin = clbutton("sin","""prnt("sin(")""",4,3,3)
	bcos = clbutton("cos","""prnt("cos(")""",4,3,4)
	btg = clbutton("tan","""prnt("tan(")""",4,3,5)
	bsw = clbutton("+/-","""prnt("-(")""",4,4,3)
	bpi = clbutton("pi","""prnt("pi")""",4,4,4)
	blog = clbutton("log","""prnt("log(,)")""",4,1,7)
	bl10 = clbutton("l 10","""prnt("log10(")""",4,1,8)
	ble = clbutton("ln","""prnt("ln(")""",4,1,9)
	basin = clbutton("asin","""prnt("asin(")""",4,3,6)
	bacos = clbutton("acos","""prnt("acos(")""",4,3,7)
	batg = clbutton("atan","""prnt("atan(")""",4,3,8)
	bmox = clbutton(chr(94)+"x","""prnt("pow(,)")""",4,2,7)
	bdodx = clbutton("root","""prnt("root(,)")""",4,2,8)
	bmo1 = clbutton(chr(94)+"-1","""prnt("pow(,-1)")""",4,2,9)
	bfac = clbutton("!","""prnt("fact(")""",4,3,9)

	bcount = clbutton("=","""reslt(do(e.get(),md.get()))""",4,4,9,True)
	bremv = clbutton("<=","""remvf()""",4,4,8,True)
	bcl = clbutton("cl","""clf()""",4,4,7,True)
	bdeg = clbutton("mod","""chmod()""",4,4,6,True)

	e.focus_set()
	okno.mainloop()

if __name__=="__main__":
	main()


#pow(pow(3,3)+sqrx(125,3)-ln(2),2)*(log(5,3)-3/5*sqrt(5))+2
#log10(sin(0.25)+acos(0.6321))/34
#asin30rad acos 30rad..sin/cos cant be larger 1
#87856246rad/deg
#cos(0.57)/sin(0.3)+(acos(0.7)-atan(0.6)) degprec
#pow(9,99999999999999999999999999999)
#asin(sin(2))

#help, keys
#deg/rad prec
#sqr x button name
#optimize code
#noselection button press visible(xview) at start
