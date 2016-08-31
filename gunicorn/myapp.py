
"""
ref:
http://qiita.com/methane/items/bc5b5128bb45dd7627b9
"""

def app(environ, start_response):
    data = b"Hello, World!\n"
    start_response("200 OK", [
        ("Content-Type", "text/plain"),
        ("Content-Length", str(len(data)))
        ])
    return iter([data])
