#pragma once
#include "./IObserver.hpp"
#include "./Subject.hpp"
#include <functional>
#include <iostream>
#include <variant>

template <class... Ts> struct Overloaded : Ts...
{
    using Ts::operator()...;
};

class Observer : public IObserver {
  public:
    Observer(Subject *subject) : subject_(subject)
    {
        if (subject_ != nullptr)
            this->subject_->Attach(this);
        this->number_ = Observer::static_number_;
    }

    Observer() : subject_(nullptr)
    {
        this->number_ = Observer::static_number_;
    }

    template <typename... Handlers>
    Observer(Handlers &&...handlers)
        : handler{[... handlers = std::move(handlers)](Event const &event) {
              std::visit(
                  Overloaded{handlers...,
                      [](auto const
                              &) { /* std::cout << "Default case\n"; */ }},
                  event);
          }}
    {
    }
    void handle(Event const &event) override
    {
        this->handler(event);
    };

    virtual ~Observer()
    {
    }

    void setSubject(Subject *subject)
    {
        this->subject_ = subject;
        if (subject_ != nullptr)
            this->subject_->Attach(this);
    };

    void deleteSubject()
    {
        if (subject_ != nullptr)
            subject_->Detach(this);
    }

  protected:
    std::function<void(Event const &)> handler;
    std::string message_from_subject_;
    Subject *subject_;
    static int static_number_;
    int number_;
};
