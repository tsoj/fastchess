#include <util/logger/logger.hpp>

#include <iomanip>
#include <thread>

#include <util/date.hpp>

namespace fast_chess {

std::atomic_bool Logger::should_log_ = false;
std::ofstream Logger::log_;
std::mutex Logger::log_mutex_;
Logger::Level Logger::level_ = Logger::Level::WARN;

void Logger::openFile(const std::string &file) {
    Logger::log_.open(file, std::ios::app);
    Logger::should_log_ = true;
}

void Logger::setLevel(Level level) { Logger::level_ = level; }

void Logger::writeToEngine(const std::string &msg, const std::string &time, const std::string &name) {
    if (!should_log_) {
        return;
    }

    const auto id = std::this_thread::get_id();

    auto fmt_message = fmt::format("[{:<6}] [{}] <{:>3}> {} <--- {}\n", "Engine", time, id, name, msg);

    const std::lock_guard<std::mutex> lock(log_mutex_);
    log_ << fmt_message << std::flush;
}

void Logger::readFromEngine(const std::string &msg, const std::string &time, const std::string &name, bool err) {
    if (!should_log_) {
        return;
    }

    const auto id = std::this_thread::get_id();

    auto fmt_message =
        fmt::format("[{:<6}] [{}] <{:>3}> {} {} ---> {}\n", "Engine", time, id, name, (err ? "1" : "2"), msg);

    const std::lock_guard<std::mutex> lock(log_mutex_);
    log_ << fmt_message << std::flush;
}

}  // namespace fast_chess