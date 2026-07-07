#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

struct Row {
    // One parsed CSV record from the metrics file.
    std::string name;
    double latency_ms;
    double throughput_tokens_per_sec;
};

std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;

    // Read each delimiter-separated piece into the result vector.
    while (std::getline(ss, field, delimiter)) {
        fields.push_back(field);
    }

    return fields;
}

bool parse_row(const std::string& line, Row& row) {
    // Expected format: name,latency_ms,throughput_tokens_per_sec
    std::vector<std::string> fields = split(line, ',');

    if (fields.size() != 3) {
        return false;
    }

    try {
        // Convert numeric fields from text to doubles.
        row.name = fields[0];
        row.latency_ms = std::stod(fields[1]);
        row.throughput_tokens_per_sec = std::stod(fields[2]);
    } catch (...) {
        // Treat malformed numbers as an invalid row.
        return false;
    }

    return true;
}

int main(int argc, char* argv[]) {
    // Use a sample file by default, or read the path passed on the command line.
    std::string filename = "data/sample_metrics.csv";

    if (argc >= 2) {
        filename = argv[1];
    }

    std::ifstream file(filename);

    // Stop early if the file cannot be opened.
    if (!file.is_open()) {
        std::cerr << "Error: could not open file: " << filename << "\n";
        return 1;
    }

    std::string line;

    // Skip header
    std::getline(file, line);

    // Track valid and invalid rows separately.
    int count = 0;
    int skipped = 0;

    // Running totals used to calculate averages after reading the file.
    double latency_sum = 0.0;
    double throughput_sum = 0.0;

    // Start below any realistic value so the first valid row becomes the max.
    double max_latency = std::numeric_limits<double>::lowest();
    double max_throughput = std::numeric_limits<double>::lowest();

    std::string max_latency_run;
    std::string max_throughput_run;

    while (std::getline(file, line)) {
        Row row;

        // Skip rows with the wrong number of fields or invalid numeric values.
        if (!parse_row(line, row)) {
            skipped++;
            continue;
        }

        // Add this row to the aggregate statistics.
        count++;
        latency_sum += row.latency_ms;
        throughput_sum += row.throughput_tokens_per_sec;

        // Keep the run name alongside each maximum value.
        if (row.latency_ms > max_latency) {
            max_latency = row.latency_ms;
            max_latency_run = row.name;
        }

        if (row.throughput_tokens_per_sec > max_throughput) {
            max_throughput = row.throughput_tokens_per_sec;
            max_throughput_run = row.name;
        }
    }

    // Avoid dividing by zero if every data row was invalid.
    if (count == 0) {
        std::cerr << "Error: no valid rows found.\n";
        return 1;
    }

    double avg_latency = latency_sum / count;
    double avg_throughput = throughput_sum / count;

    // Print all floating-point results with two decimal places.
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "Parsed rows: " << count << "\n";
    std::cout << "Skipped rows: " << skipped << "\n\n";

    std::cout << "Average latency: " << avg_latency << " ms\n";
    std::cout << "Max latency: " << max_latency << " ms"
              << " (" << max_latency_run << ")\n\n";

    std::cout << "Average throughput: " << avg_throughput << " tokens/sec\n";
    std::cout << "Max throughput: " << max_throughput << " tokens/sec"
              << " (" << max_throughput_run << ")\n";

    return 0;
}
