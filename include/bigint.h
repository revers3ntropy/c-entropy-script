#pragma once

#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <math.h>
#include <map>

#include "util.h"


/* Single class BigNumber, all contained in this header file
 * Uses two integer values to store any real number,
 * meaning that in this case 0.1+0.2 == 0.3.
 * Converting back to string requires removing a bunch of detail however,
 * as it converts the result of actually dividing them together into a float before casting to string
 */

using ll = long long int;
using ull = unsigned long long int;

namespace es {
    struct BigNumber {
        ll numerator;
        ull denominator;

        BigNumber () {
            numerator = 0;
            denominator = 1;
        }

        explicit BigNumber (std::string number) {

            std::vector<std::string>* parts = util::split(number.c_str(), '.');

            if (parts->size() > 2) {
                // has multiple decimal points ==> invalid
                numerator = 0;
                denominator = 0;
            } else if (parts->size() == 1) {
                // is a simple int
                try {
                    numerator = std::stoll((*parts)[0]);
                } catch (std::out_of_range &e) {
                    numerator = std::numeric_limits<ll>::max();
                }
                denominator = 1;
            } else {
                // has fractional part
                number.erase(std::remove(number.begin(), number.end(), '.'), number.end());
                numerator = std::stoi(number);
                denominator = pow(10, ((*parts)[1].size()));
                simplify();
            }
        }

        BigNumber(ll nu, ull de) :
            numerator(nu), denominator(de) {
            simplify();
        }

        [[nodiscard]] std::string str () const {
            if (denominator == 0){
                return "inf";
            }
            if (denominator == 1){
                return std::to_string(numerator);
            }
            if (numerator == 0){
                return "0";
            }


            // from https://www.geeksforgeeks.org/represent-the-fraction-of-two-numbers-in-the-string-format/

            // Output string to store the answer
            std::string res;

            // only numerator is signed
            int sign = numerator < 0 ? -1 : 1;

            ull num = numerator;
            ull den = denominator;

            if (sign == -1){
                res += "-";
            }

            // Calculate the absolute part (before decimal point)
            ull initial = num / den;

            // Append the initial part
            res += std::to_string(initial);

            // If completely divisible, return answer.
            if (num % den == 0){
                return res;
            }

            res += ".";

            // Initialize Remainder
            int rem = num % den;
            std::map<ll, ll> mp;

            // Position at which fraction starts repeating
            // if it exists
            ull index;
            bool repeating = false;
            while (rem > 0 && !repeating) {

                // If this remainder is already seen,
                // then there exists a repeating fraction.
                if (mp.find(rem) != mp.end()) {

                    // Index to insert parentheses
                    index = mp[rem];
                    repeating = true;
                    break;
                } else {
                    mp[rem] = res.size();
                }

                rem = rem * 10;

                // Calculate quotient, append
                // it to result and
                // calculate next remainder
                ull temp = rem / den;
                res += std::to_string(temp);
                rem = rem % den;
            }

            // If repeating fraction exists,
            // insert parentheses.
            if (repeating) {
                res += ")";
                res.insert(index, "(");
            }

            // Return result.
            return res;
        }

        void simplify () {
            if (denominator == 0) {
                return;
            }

            ull gcd = std::__gcd((ull)std::abs(numerator), denominator);
            numerator /= gcd;
            denominator /= gcd;
        }

        BigNumber* operator + (ll n) const {
            if (n == 0) {
                return new BigNumber(numerator, denominator);
            }
            ll mod = 1;
            if (n < 0) {
                n *= -1;
                mod *= -1;
            }
            return new BigNumber(ll(numerator + n*denominator), denominator);
        }
        BigNumber* operator - (ll n) const {
            if (n == 0) {
                return new BigNumber(numerator, denominator);
            }
            ll mod = 1;
            if (n < 0) {
                n *= -1;
                mod *= -1;
            }
            return new BigNumber(ll((numerator*mod) - n * denominator), denominator);
        }
        BigNumber* operator * (ll n) const {
            if (n == 0) {
                return new BigNumber(0, 1);
            }
            ll mod = 1;
            if (n < 0) {
                n *= -1;
                mod *= -1;
            }
            return new BigNumber(numerator * mod * n, denominator);
        }
        BigNumber* operator / (ll n) const {
            if (n == 0) {
                return new BigNumber(0, 0);
            }
            ll mod = 1;
            if (n < 0) {
                n *= -1;
                mod *= -1;
            }
            return new BigNumber(numerator * mod, denominator * n);
        }


        BigNumber* operator + (BigNumber n) const {
            return new BigNumber(
                (ll)(numerator * n.denominator + n.numerator * denominator),
                denominator * n.denominator
            );
        }
        BigNumber* operator - (BigNumber n) const {
            return new BigNumber(
                (ll)(numerator * n.denominator - n.numerator * denominator),
                denominator * n.denominator
            );
        }
        BigNumber* operator * (BigNumber n) const {
            return new BigNumber(
                numerator * n.numerator,
                denominator * n.denominator
            );
        }
        BigNumber* operator / (BigNumber n) const {
            return new BigNumber(
                (ll)(numerator * n.denominator),
                denominator * n.numerator
            );
        }

        BigNumber* operator + (BigNumber* n) const {
            return new BigNumber(
                    (ll)(numerator * n->denominator + n->numerator * denominator),
                    denominator * n->denominator
            );
        }
        BigNumber* operator - (BigNumber* n) const {
            return new BigNumber(
                    (ll)(numerator * n->denominator - n->numerator * denominator),
                    denominator * n->denominator
            );
        }
        BigNumber* operator * (BigNumber* n) const {
            return new BigNumber(
                    numerator * n->numerator,
                    denominator * n->denominator
            );
        }
        BigNumber* operator / (BigNumber* n) const {
            return new BigNumber(
                    (ll)(numerator * n->denominator),
                    denominator * n->numerator
            );
        }
    };
}