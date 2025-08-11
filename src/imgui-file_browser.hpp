#pragma once

#include <vector>
#include <filesystem>
#include <span>
#include <unordered_set>

// ReSharper disable once CppInconsistentNaming
namespace ImGui
{
	enum class FileBrowserFlags : std::uint32_t
	{
		NONE = 0,

		// ============================
		// WINDOW
		// ============================
		NO_TITLEBAR = 0b0000'0000'0000'0001,
		NO_MODAL = 0b0000'0000'0000'0010,

		// ============================
		// INTERACTIVE
		// ============================

		CLOSE_ON_ESCAPE = 0b0000'0000'0001'0000,
		CONFIRM_ON_ENTER = 0b0000'0000'0010'0000,

		// ============================
		// SELECTION
		// ============================

		SELECT_DIRECTORY = 0b0000'0001'0000'0000,
		HIDE_REGULAR_FILES = 0b0000'0010'0000'0000,
		MULTIPLE_SELECTION = 0b0000'0010'0000'0000,

		// ============================
		// PATH
		// ============================

		PATH_EDITABLE = 0b0001'0000'0000'0000,
	};

	class FileBrowser final
	{
	public:
		using size_type = int;

		constexpr static std::string_view parent_path_name{"(last level)"};

		constexpr static std::string_view wildcard_filter{".*"};

	private:
		enum class State : std::uint32_t
		{
			NONE = 0b0000'0000'0000'0000,

			// ========================
			// position
			// ========================

			POSITION_DIRTY = 0b0000'0000'0000'0001,

			// ========================
			// WINDOW
			// ========================

			OPENING = 0b0000'0000'0001'0000,
			CLOSING = 0b0000'0000'0010'0000,
			OPENED = 0b0000'0000'0100'0000,

			// ========================
			// SELECTION
			// ========================

			SELECTED = 0b0000'0001'0000'0000,

			// ========================
			// PATH
			// ========================

			EDITING_PATH = 0b0001'0000'0000'0000,
			FOCUSING_PATH_EDITOR_NEXT_FRAME = 0b0010'0000'0000'0000,
		};

		struct file_descriptor
		{
			std::filesystem::path name;
			std::filesystem::path extension;

			std::string display_name;
			bool is_directory;
		};

		std::string title_;

		size_type x_;
		size_type y_;
		size_type width_;
		size_type height_;

		FileBrowserFlags flags_;
		// avoid padding
		State states_;

		// ========================
		// path
		// ========================

		std::filesystem::path working_directory_;
		std::string edit_working_directory_buffer_;

		// ========================
		// selection
		// ========================

		std::unordered_set<std::filesystem::path> selected_filenames_;

		// ========================
		// filter
		// ========================

		// [0]: wildcard filter (*)
		// [0]: combined filter
		std::vector<std::string> filters_;
		std::vector<std::string>::difference_type selected_filter_;

		// ========================
		// file descriptor
		// ========================

		std::vector<file_descriptor> file_descriptors_;

		// ========================
		// tooltip
		// ========================

		std::string tooltip_;

		[[nodiscard]] auto has_state(State state) const noexcept -> bool;

		auto append_state(State state) noexcept -> void;

		auto clear_state(State state) noexcept -> void;

		// ========================
		// filter
		// ========================

		[[nodiscard]] auto is_filter_matched(const std::filesystem::path& extension) const noexcept -> bool;

		[[nodiscard]] auto has_combined_filter() const noexcept -> bool;

		// ========================
		// file descriptor
		// ========================

		auto update_file_descriptors() noexcept -> void;

	public:
		FileBrowser(const FileBrowser&) noexcept = delete;
		FileBrowser(FileBrowser&&) noexcept = default;
		auto operator=(const FileBrowser&) noexcept -> FileBrowser& = delete;
		auto operator=(FileBrowser&&) noexcept -> FileBrowser& = default;

		~FileBrowser() noexcept;

		explicit FileBrowser(
			std::string_view title,
			size_type x,
			size_type y,
			size_type width,
			size_type height,
			FileBrowserFlags flags,
			std::filesystem::path open_directory = std::filesystem::current_path()
		) noexcept;

		explicit FileBrowser(
			std::string_view title,
			size_type width,
			size_type height,
			FileBrowserFlags flags,
			std::filesystem::path open_directory = std::filesystem::current_path()
		) noexcept;

		explicit FileBrowser(
			std::string_view title,
			FileBrowserFlags flags,
			std::filesystem::path open_directory = std::filesystem::current_path()
		) noexcept;

		explicit FileBrowser(
			std::string_view title,
			std::filesystem::path open_directory = std::filesystem::current_path()
		) noexcept;

		// ========================
		// title
		// ========================

		[[nodiscard]] auto get_title() const noexcept -> std::string_view;

		auto set_title(std::string_view title) noexcept -> void;

		// ========================
		// position
		// ========================

		[[nodiscard]] auto get_position_x() const noexcept -> size_type;

		[[nodiscard]] auto get_position_y() const noexcept -> size_type;

		auto set_position(size_type x, size_type y) noexcept -> void;

		auto set_position_x(size_type x) noexcept -> void;

		auto set_position_y(size_type y) noexcept -> void;

		// ========================
		// size
		// ========================

		[[nodiscard]] auto get_size_width() const noexcept -> size_type;

		[[nodiscard]] auto get_size_height() const noexcept -> size_type;

		auto set_size(size_type width, size_type height) noexcept -> void;

		auto set_size_width(size_type width) noexcept -> void;

		auto set_size_height(size_type height) noexcept -> void;

		// ========================
		// flags
		// ========================

		[[nodiscard]] auto has_flag(FileBrowserFlags flag) const noexcept -> bool;

		[[nodiscard]] auto get_flags() const noexcept -> FileBrowserFlags;

		auto append_flags(FileBrowserFlags flags) noexcept -> void;

		auto append_flags(std::initializer_list<FileBrowserFlags> flags) noexcept -> void;

		template<typename... T>
			requires(std::is_same_v<T, FileBrowserFlags> and ...)
		auto append_flags(T... flags) noexcept -> void
		{
			(append_flags(flags), ...);
		}

		auto set_flags(FileBrowserFlags flags) noexcept -> void;

		auto set_flags(std::initializer_list<FileBrowserFlags> flags) noexcept -> void;

		template<typename... T>
			requires(std::is_same_v<T, FileBrowserFlags> and ...)
		auto set_flags(T... flags) noexcept -> void
		{
			set_flags(FileBrowserFlags::NONE);
			append_flags(flags...);
		}

		// ========================
		// path
		// ========================

		[[nodiscard]] auto get_working_directory() const noexcept -> const std::filesystem::path&;

		auto set_working_directory(const std::filesystem::path& directory = std::filesystem::current_path()) noexcept -> bool;

		// ========================
		// window
		// ========================

		[[nodiscard]] auto is_opened() const noexcept -> bool;

		auto open() noexcept -> void;

		[[nodiscard]] auto is_closed() const noexcept -> bool;

		auto close() noexcept -> void;

		auto show() noexcept -> void;

		// ========================
		// selection
		// ========================

		[[nodiscard]] auto has_selected() const noexcept -> bool;

		[[nodiscard]] auto get_selected() const noexcept -> std::filesystem::path;

		[[nodiscard]] auto get_all_selected() const noexcept -> std::vector<std::filesystem::path>;

		auto clear_selected() noexcept -> void;

		// ========================
		// filter
		// ========================

		[[nodiscard]] auto get_filter() const noexcept -> const std::vector<std::string>&;

		auto set_filter(std::span<const std::string_view> filters) noexcept -> void;

		auto set_filter(std::span<const std::string> filters) noexcept -> void;

		auto set_filter(const std::vector<std::string>& filters) noexcept -> void;

		auto clear_filter() noexcept -> void;
	};
}
