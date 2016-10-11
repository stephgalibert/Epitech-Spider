//
// SoLoader.cpp for server in /home/galibe_s/project/SpiderServer/utils
//
// Made by stephane galibert
// Login   <galibe_s@epitech.net>
//
// Started on  Sun Aug  7 20:08:53 2016 stephane galibert
// Last update Fri Aug 19 17:36:35 2016 stephane galibert
//

#include "SoLoader.hpp"

SoLoader::SoLoader(void)
{
  _name = "";
  _ld = NULL;
}

SoLoader::SoLoader(std::string const& name)
{
  _name = name;
  _ld = NULL;
}

SoLoader::~SoLoader(void)
{
  if (_ld)
    dlclose(_ld);
}

void SoLoader::setLibName(std::string const& lib)
{
  if (_ld)
    dlclose(_ld);
  _name = lib;
}

void SoLoader::load(void)
{
  _ld = dlopen(_name.data(), RTLD_NOW);
  if (!_ld)
    throw (std::runtime_error(dlerror()));
}

void *SoLoader::sym(std::string const& symbol) const
{
  void *sym = NULL;
  char *error = NULL;

  dlerror();
  if (_ld) {
    sym = dlsym(_ld, symbol.c_str());
    error = dlerror();
    if (error) {
      throw (std::runtime_error(error));
    }
  }
  return (sym);
}

std::string const& SoLoader::getLibName(void) const
{
  return (_name);
}
