from PIL import Image
import pytesseract as pyt
import sys, os

file = '3.jpeg'

if __name__ == '__main__':
	if len(sys.argv) == 2:
		file = sys.argv[1]

os.system(os.getcwd() + '/unwarp ' + file)

img = Image.open('result.jpeg')
print(pyt.image_to_string(img))