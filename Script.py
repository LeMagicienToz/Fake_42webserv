#!/usr/bin/env python3

import os
import sys

print("")
print("<html><head><title>CGI Script</title></head><body>")
print("<h1>Hello from the CGI script!</h1>")
print(f"<p>Request Method: {os.environ.get('REQUEST_METHOD')}</p>")
print(f"<p>Server Protocol: {os.environ.get('SERVER_PROTOCOL')}</p>")
print(f"<p>CONTENT_TYPE: {os.environ.get('CONTENT_TYPE')}</p>")
print(f"<p>CONTENT_LENGTH: {os.environ.get('CONTENT_LENGTH')}</p>")
print(f"<p>HTTP_ACCEPT: {os.environ.get('HTTP_ACCEPT')}</p>")
print(f"<p>SERVER_NAME: {os.environ.get('SERVER_NAME')}</p>")
print(f"<p>HTTP_USER_AGENT: {os.environ.get('HTTP_USER_AGENT')}</p>")
print(f"<p>HTTP_ACCEPT: {os.environ.get('HTTP_ACCEPT')}</p>")
print(f"<p>HTTP_ACCEPT_ENCODING: {os.environ.get('HTTP_ACCEPT_ENCODING')}</p>")
print(f"<p>HTTP_ACCEPT_LANGUAGE: {os.environ.get('HTTP_ACCEPT_LANGUAGE')}</p>")
print("</body></html>")
# sys.stdout.flush()
