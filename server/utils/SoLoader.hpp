//
// SoLoader.hpp for soloader in /home/galibe_s/cpp_utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Mon Apr 11 02:50:49 2016 stephane galibert
// Last update Tue Oct  4 21:14:10 2016 stephane galibert
//

#ifndef _SOLOADER_HPP_
# define _SOLOADER_HPP_

# include <iostream>
# include <string>
# include <dlfcn.h>
# include <stdexcept>

#include <boost/noncopyable.hpp>

class SoLoader : private boost::noncopyable
{
public:
  SoLoader(void);
  SoLoader(std::string const& name);
  ~SoLoader(void);

  void setLibName(std::string const& lib);
  void load(void);
  void *sym(std::string const& symbol) const;

  std::string const& getLibName(void) const;
private:
  std::string _name;
  void *_ld;
};

#endif /* !_SOLOADER_HPP_ */
