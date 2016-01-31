import pypic
filename = "car1.jpg"
with pypic as pp:
	if "." in filename:
		ext = filename.split(".")[-1]
		ext = ext if ext in pp.extensions else "unknown"
	else:
		ext = "unknown"
	print(pp.getrgb("car1.jpg", pp.extensions[ext]))
