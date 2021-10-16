#pragma once
#include "./IObserver.hpp"
#include "./Subject.hpp"

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

    virtual ~Observer()
    {
    }

    void setSubject(Subject *subject)
    {
        this->subject_ = subject;
        if (subject_ != nullptr)
            this->subject_->Attach(this);
    };

    void Update(EventType eventType, const std::string &msg) override
    {
        message_from_subject_ = msg;
        PrintInfo();
    }

    void RemoveMeFromTheList()
    {
        if (subject_ != nullptr)
            subject_->Detach(this);
        std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
    }

    void PrintInfo()
    {
        std::cout << "Observer \"" << this->number_
                  << "\": a new message is available --> "
                  << this->message_from_subject_ << "\n";
    }

  protected:
    std::string message_from_subject_;
    Subject *subject_;
    static int static_number_;
    int number_;
};
