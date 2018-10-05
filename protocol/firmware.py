from protocol import recive
from protocol import send
from console import debugprint

def uploadsource(sourcepath):
    if sourcepath.endswith('.ino') == False:
        debugprint('FileNameError', 'Defined file not is arduino firmware.')
    pass