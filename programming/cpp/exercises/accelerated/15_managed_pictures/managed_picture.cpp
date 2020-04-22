// managed_picture.h
// A managed picture class.

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "managed_pointer.cpp"

class Picture;

class Picture_Base {
public:
  virtual Picture_Base *clone() const = 0;
  virtual ~Picture_Base() {}

private:
  typedef std::vector<std::string>::size_type height_type;
  typedef std::string::size_type width_type;

  virtual void display(std::ostream &os, height_type line_index,
                       bool do_pad) const = 0;
  virtual height_type height() const = 0;
  virtual width_type width() const = 0;
  virtual void reframe_fancy(char frame_corner, char frame_top_bottom,
                             char frame_side) = 0;

protected:
  static void pad(std::ostream &os, width_type begin, width_type end) {
    while (begin != end) {
      os << " ";
      ++begin;
    }
  }

  friend class Picture_String;
  friend class Picture_Framed;
  friend class Picture_Framed_Fancy;
  friend class Picture_HCat;
  friend class Picture_HCat_Centered;
  friend class Picture_VCat;
  friend std::ostream &operator<<(std::ostream &os, const Picture &picture);
  friend void reframe_fancy(const Picture &picture, char frame_char);
  friend void reframe_fancy(const Picture &picture, char frame_corner,
                            char frame_top_bottom, char frame_side);
};

class Picture {
public:
  Picture(const std::vector<std::string> &lines = std::vector<std::string>());

private:
  Picture(Picture_Base *picture) : picture_(picture) {}
  ManagedPointer<Picture_Base> picture_;

  friend Picture frame(const Picture &picture);
  friend Picture frame_fancy(const Picture &picture);
  friend Picture frame_fancy(const Picture &picture, char frame_corner,
                             char frame_top_bottom, char frame_side);
  friend void reframe_fancy(const Picture &picture, char frame_char);
  friend void reframe_fancy(const Picture &picture, char frame_corner,
                            char frame_top_bottom, char frame_side);
  friend Picture hcat(const Picture &left, const Picture &right);
  friend Picture hcat_centered(const Picture &left, const Picture &right);
  friend Picture vcat(const Picture &top, const Picture &bottom);
  friend std::ostream &operator<<(std::ostream &os, const Picture &picture);
};

Picture frame(const Picture &picture);
Picture frame_fancy(const Picture &picture);
Picture frame_fancy(const Picture &picture, char frame_corner,
                    char frame_top_bottom, char frame_side);
Picture hcat(const Picture &left, const Picture &right);
Picture hcat_centered(const Picture &left, const Picture &right);
Picture vcat(const Picture &top, const Picture &bottom);
std::ostream &operator<<(std::ostream &os, const Picture &picture);

class Picture_String : public Picture_Base {
  Picture_String(const std::vector<std::string> &lines) : lines_(lines) {}
  ~Picture_String() {}

  Picture_Base *clone() const { return new Picture_String(lines_); }

  void display(std::ostream &os, height_type line_index, bool do_pad) const {
    if (line_index < height()) {
      os << lines_[line_index];
    }
    if (do_pad) {
      pad(os, line_index < height() ? lines_[line_index].size() : 0, width());
    }
  }
  height_type height() const { return lines_.size(); }
  width_type width() const {
    Picture_Base::width_type w = 0;
    for (Picture_Base::height_type i = 0; i != lines_.size(); ++i) {
      w = std::max(w, lines_[i].size());
    }
    return w;
  }
  void reframe_fancy(char frame_corner, char frame_top_bottom,
                     char frame_side) {
    // There is nothing to be done in order to reframe a Frame_String. We use
    // the following lines to indicate that nothing needs to be done, and
    // suppress warnings about unused variables.
    (void)frame_corner;
    (void)frame_top_bottom;
    (void)frame_side;
  }

  std::vector<std::string> lines_;

  friend class Picture;
  friend Picture::Picture(const std::vector<std::string> &lines);
};

class Picture_Framed : public Picture_Base {
  Picture_Framed(const ManagedPointer<Picture_Base> &picture)
      : picture_(picture) {}
  ~Picture_Framed() {}

  Picture_Base *clone() const { return new Picture_Framed(picture_); }

  void display(std::ostream &os, height_type line_index, bool do_pad) const {
    if (line_index < height()) {
      if (line_index == 0 || line_index == height() - 1) {
        os << std::string(width(), '*');
      } else if (line_index == 1 || line_index == height() - 2) {
        os << '*';
        pad(os, 1, width() - 1);
        os << '*';
      } else {
        os << "* ";
        picture_->display(os, line_index - 2, true);
        os << " *";
      }
    } else {
      if (do_pad) {
        pad(os, 0, width());
      }
    }
  }
  height_type height() const { return picture_->height() + 4; }
  width_type width() const { return picture_->width() + 4; }
  void reframe_fancy(char frame_corner, char frame_top_bottom,
                     char frame_side) {
    // There is nothing to be done in order to reframe a Frame_String. We use
    // the following lines to indicate that nothing needs to be done, and
    // suppress warnings about unused variables.
    (void)frame_corner;
    (void)frame_top_bottom;
    (void)frame_side;
  }

  ManagedPointer<Picture_Base> picture_;

  friend Picture frame(const Picture &picture);
};

class Picture_Framed_Fancy : public Picture_Base {
  Picture_Framed_Fancy(const ManagedPointer<Picture_Base> &picture)
      : picture_(picture), frame_corner_('*'), frame_top_bottom_('*'),
        frame_side_('*') {}
  Picture_Framed_Fancy(const ManagedPointer<Picture_Base> &picture,
                       char frame_char)
      : picture_(picture), frame_corner_(frame_char),
        frame_top_bottom_(frame_char), frame_side_(frame_char) {}
  Picture_Framed_Fancy(const ManagedPointer<Picture_Base> &picture,
                       char frame_corner, char frame_top_bottom,
                       char frame_side)
      : picture_(picture), frame_corner_(frame_corner),
        frame_top_bottom_(frame_top_bottom), frame_side_(frame_side) {}
  ~Picture_Framed_Fancy() {}

  Picture_Base *clone() const {
    return new Picture_Framed_Fancy(picture_, frame_corner_, frame_top_bottom_,
                                    frame_side_);
  }

  void display(std::ostream &os, height_type line_index, bool do_pad) const {
    if (line_index < height()) {
      if (line_index == 0 || line_index == height() - 1) {
        os << frame_corner_ << std::string(width() - 2, frame_top_bottom_)
           << frame_corner_;
      } else if (line_index == 1 || line_index == height() - 2) {
        os << frame_side_;
        pad(os, 1, width() - 1);
        os << frame_side_;
      } else {
        os << frame_side_ << ' ';
        picture_->display(os, line_index - 2, true);
        os << ' ' << frame_side_;
      }
    } else {
      if (do_pad) {
        pad(os, 0, width());
      }
    }
  }
  height_type height() const { return picture_->height() + 4; }
  width_type width() const { return picture_->width() + 4; }
  void reframe_fancy(char frame_corner, char frame_top_bottom,
                     char frame_side) {
    frame_corner_ = frame_corner;
    frame_top_bottom_ = frame_top_bottom;
    frame_side_ = frame_side;
  }

  ManagedPointer<Picture_Base> picture_;
  char frame_corner_, frame_top_bottom_, frame_side_;

  friend Picture frame_fancy(const Picture &picture);
  friend Picture frame_fancy(const Picture &picture, char frame_corner,
                             char frame_top_bottom, char frame_side);
};

class Picture_HCat : public Picture_Base {
  Picture_HCat(const ManagedPointer<Picture_Base> &left,
               const ManagedPointer<Picture_Base> &right)
      : left_(left), right_(right) {}
  ~Picture_HCat() {}

  Picture_Base *clone() const { return new Picture_HCat(left_, right_); }

  void display(std::ostream &os, height_type line_index, bool do_pad) const {
    left_->display(os, line_index, do_pad || line_index < right_->height());
    right_->display(os, line_index, do_pad);
  }
  height_type height() const {
    return std::max(left_->height(), right_->height());
  }
  width_type width() const { return left_->width() + right_->width(); }
  void reframe_fancy(char frame_corner, char frame_top_bottom,
                     char frame_side) {
    left_.make_unique();
    left_->reframe_fancy(frame_corner, frame_top_bottom, frame_side);
    right_.make_unique();
    right_->reframe_fancy(frame_corner, frame_top_bottom, frame_side);
  }

  ManagedPointer<Picture_Base> left_, right_;

  friend Picture hcat(const Picture &left, const Picture &right);
};

class Picture_HCat_Centered : public Picture_Base {
  Picture_HCat_Centered(const ManagedPointer<Picture_Base> &left,
                        const ManagedPointer<Picture_Base> &right)
      : left_(left), right_(right) {}
  ~Picture_HCat_Centered() {}

  Picture_Base *clone() const {
    return new Picture_HCat_Centered(left_, right_);
  }

  void display(std::ostream &os, height_type line_index, bool do_pad) const {
    if (left_->height() < right_->height()) {
      height_type pad_lines = (right_->height() - left_->height()) / 2;

      if (line_index >= pad_lines) {
        left_->display(os, line_index - pad_lines,
                       do_pad || line_index < right_->height());
      } else {
        left_->display(os, left_->height(),
                       do_pad || line_index < right_->height());
      }

      right_->display(os, line_index, do_pad);
      return;
    }

    if (left_->height() > right_->height()) {
      height_type pad_lines = (left_->height() - right_->height()) / 2;

      left_->display(os, line_index, do_pad || line_index < right_->height());

      if (line_index >= pad_lines) {
        right_->display(os, line_index - pad_lines, do_pad);
      } else {
        right_->display(os, right_->height(), do_pad);
      }

      return;
    }

    left_->display(os, line_index, do_pad || line_index < right_->height());
    right_->display(os, line_index, do_pad);
  }
  height_type height() const {
    return std::max(left_->height(), right_->height());
  }
  width_type width() const { return left_->width() + right_->width(); }
  void reframe_fancy(char frame_corner, char frame_top_bottom,
                     char frame_side) {
    left_.make_unique();
    left_->reframe_fancy(frame_corner, frame_top_bottom, frame_side);
    right_.make_unique();
    right_->reframe_fancy(frame_corner, frame_top_bottom, frame_side);
  }

  ManagedPointer<Picture_Base> left_, right_;

  friend Picture hcat_centered(const Picture &left, const Picture &right);
};

class Picture_VCat : public Picture_Base {
  Picture_VCat(const ManagedPointer<Picture_Base> &top,
               const ManagedPointer<Picture_Base> &bottom)
      : top_(top), bottom_(bottom) {}
  ~Picture_VCat() {}

  Picture_Base *clone() const { return new Picture_VCat(top_, bottom_); }

  void display(std::ostream &os, height_type line_index, bool do_pad) const {
    width_type start_pad = 0;
    if (line_index < top_->height()) {
      top_->display(os, line_index, do_pad);
      start_pad = top_->width();
    } else if (line_index < height()) {
      bottom_->display(os, line_index - top_->height(), do_pad);
      start_pad = bottom_->width();
    }
    if (do_pad) {
      pad(os, start_pad, width());
    }
  }
  height_type height() const { return top_->height() + bottom_->height(); }
  width_type width() const { return std::max(top_->width(), bottom_->width()); }
  void reframe_fancy(char frame_corner, char frame_top_bottom,
                     char frame_side) {
    top_.make_unique();
    top_->reframe_fancy(frame_corner, frame_top_bottom, frame_side);
    bottom_.make_unique();
    bottom_->reframe_fancy(frame_corner, frame_top_bottom, frame_side);
  }

  ManagedPointer<Picture_Base> top_, bottom_;

  friend Picture vcat(const Picture &top, const Picture &bottom);
};

Picture::Picture(const std::vector<std::string> &lines)
    : picture_(new Picture_String(lines)) {}

Picture frame(const Picture &picture) {
  return new Picture_Framed(picture.picture_);
}

Picture frame_fancy(const Picture &picture) {
  return new Picture_Framed_Fancy(picture.picture_);
}

Picture frame_fancy(const Picture &picture, char frame_corner,
                    char frame_top_bottom, char frame_side) {
  return new Picture_Framed_Fancy(picture.picture_, frame_corner,
                                  frame_top_bottom, frame_side);
}

void reframe_fancy(const Picture &picture, char frame_char) {
  picture.picture_->reframe_fancy(frame_char, frame_char, frame_char);
}

void reframe_fancy(const Picture &picture, char frame_corner,
                   char frame_top_bottom, char frame_side) {
  picture.picture_->reframe_fancy(frame_corner, frame_top_bottom, frame_side);
}

Picture hcat(const Picture &left, const Picture &right) {
  return new Picture_HCat(left.picture_, right.picture_);
}

Picture hcat_centered(const Picture &left, const Picture &right) {
  return new Picture_HCat_Centered(left.picture_, right.picture_);
}

Picture vcat(const Picture &top, const Picture &bottom) {
  return new Picture_VCat(top.picture_, bottom.picture_);
}

std::ostream &operator<<(std::ostream &os, const Picture &picture) {
  const Picture_Base::height_type height = picture.picture_->height();
  for (Picture_Base::height_type i = 0; i != height; ++i) {
    picture.picture_->display(os, i, false);
    os << std::endl;
  }
  return os;
}
