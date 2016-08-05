#-*- coding:utf-8 -*-

# import flask
# import bottle

# app = flask.Flask(__name__)
# bottle_app = bottle.app()

# @bottle_app.route('/')
# @app.route('/')
# def index():
#     return b"Hello, World"

def wsgi(env, start):
    c = b"Hello, World"
    start("200 OK", [('Content-Type', 'text/plain'), ('Content-Length', str(len(c)))])
    return [c]

# 起動方法
# Flask:  gunicorn -k meinheld.gmeinheld.MeinheldWorker -b :6000 app:app
# Bottle: gunicorn -k meinheld.gmeinheld.MeinheldWorker -b :6000 app:bottle_app
# wsgi:   gunicorn -k meinheld.gmeinheld.MeinheldWorker -b :6000 app:wsgi
