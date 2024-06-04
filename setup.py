from setuptools import setup

APP_NAME = 'SmartCalc_Taleayos'
APP = ['main.py']
DATA_FILES = []
OPTIONS = {
    'iconfile': 'other/icon.icns',
    'packages': ['PyQt5', 'numpy', 'matplotlib']
}

setup(
    app=APP,
    name=APP_NAME,
    data_files=DATA_FILES,
    options={'py2app': OPTIONS},
    setup_requires=['py2app'],
)