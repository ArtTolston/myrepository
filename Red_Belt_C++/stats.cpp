#include "stats.h"
#include "http_request.h"
#include <iostream>
using namespace std;

void Stats::AddMethod(string_view method) {
	auto it = methods_dict.find(method);
	if (it == end(methods_dict)) {
		++methods_dict["UNKNOWN"];
	}
	else {
		++methods_dict[method];
	}
}

void Stats::AddUri(string_view uri) {
	auto it = uris_dict.find(uri);
	if (it == end(uris_dict)) {
		++uris_dict["unknown"];
	}
	else {
		++uris_dict[uri];
	}
}

const map<string_view, int>& Stats::GetMethodStats() const {
	return methods_dict;
}

const map<string_view, int>& Stats::GetUriStats() const {
	return uris_dict;
}

HttpRequest ParseRequest(string_view line) {
	HttpRequest request;
	size_t pos = 0, from = 0;
	pos = line.find_first_not_of(" ", pos);
	line = line.substr(pos);
	pos = 0;
	pos = line.find(" ", pos);
	request.method = line.substr(from, pos);
	++pos;
	from = pos;
	pos = line.find(" ", pos);
	request.uri = line.substr(from, pos - request.method.size() - 1);
	++pos;
	from = pos;
	request.protocol = line.substr(from, line.npos);
	return request;
}


