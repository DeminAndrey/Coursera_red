#include "stats.h"
#include "http_request.h"

Stats::Stats() {
    method_stats["GET"] = 0;
    method_stats["POST"] = 0;
    method_stats["PUT"] = 0;
    method_stats["DELETE"] = 0;
    method_stats["UNKNOWN"] = 0;

    uri_stats["/"] = 0;
    uri_stats["/order"] = 0;
    uri_stats["/product"] = 0;
    uri_stats["/basket"] = 0;
    uri_stats["/help"] = 0;
    uri_stats["unknown"] = 0;
}

void Stats::AddMethod(string_view method) {
    if (method == "GET") {
        method_stats["GET"]++;
    } else if (method == "POST") {
        method_stats["POST"]++;
    } else if (method == "PUT") {
        method_stats["PUT"]++;
    } else if (method == "DELETE") {
        method_stats["DELETE"]++;
    } else {
        method_stats["UNKNOWN"]++;
    }
}

void Stats::AddUri(string_view uri) {
    if (uri == "/") {
        uri_stats["/"]++;
    } else if (uri == "/order") {
        uri_stats["/order"]++;
    } else if (uri == "/product") {
        uri_stats["/product"]++;
    } else if (uri == "/basket") {
        uri_stats["/basket"]++;
    } else if (uri == "/help") {
        uri_stats["/help"]++;
    } else {
        uri_stats["unknown"]++;
    }
}

const map<string_view, int>& Stats::GetMethodStats() const {
    return method_stats;
}

const map<string_view, int>& Stats::GetUriStats() const {
    return uri_stats;
}

HttpRequest ParseRequest(string_view line) {
    HttpRequest request;
    size_t start = line.find_first_not_of(" ");
    if (start > 0) {
        size_t pos = line.find_first_not_of(" ");
        line.remove_prefix(pos);
    }
    size_t space = line.find(" ");
    request.method = line.substr(0, space);
    line.remove_prefix(space + 1);
    space = line.find(" ");
    request.uri = line.substr(0, space);
    line.remove_prefix(space + 1);
    request.protocol = line.substr(0, line.size());
    line.remove_prefix(line.size());
    return request;
}