#include <gtkmm.h>
#include <iostream>

Gtk::ApplicationWindow *pAppWindow = nullptr;

static void on_button_clicked()
{
  if (pAppWindow)
    pAppWindow->hide(); // hide() will cause main::run() to end.
}

int main(int argc, char **argv)
{
  auto app = Gtk::Application::create(argc, argv, "dev.webimizer.example");

  // Load the GtkBuilder file and instantiate its widgets:
  auto refBuilder = Gtk::Builder::create();
  try
  {
    refBuilder->add_from_file("basic.glade");
  }
  catch (const Glib::FileError &ex)
  {
    std::cerr << "FileError: " << ex.what() << std::endl;
    return 1;
  }
  catch (const Glib::MarkupError &ex)
  {
    std::cerr << "MarkupError: " << ex.what() << std::endl;
    return 1;
  }
  catch (const Gtk::BuilderError &ex)
  {
    std::cerr << "BuilderError: " << ex.what() << std::endl;
    return 1;
  }

  // Get the GtkBuilder-instantiated Dialog:
  refBuilder->get_widget("main_window", pAppWindow);
  if (pAppWindow)
  {
    // Get the GtkBuilder-instantiated Button, and connect a signal handler:
    Gtk::Button *pButton = nullptr;
    refBuilder->get_widget("quit_button", pButton);
    if (pButton)
    {
      pButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
    }

    app->run(*pAppWindow);
  }

  delete pAppWindow;

  return 0;
}