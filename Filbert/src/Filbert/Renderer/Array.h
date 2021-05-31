#pragma once


namespace Filbert
{
    class Array
    {
    public:
        virtual ~Array() {};

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Array* Create();
    };
}