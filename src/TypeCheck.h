#pragma once
#include "Stella/Absyn.H"

#include <cassert>
#include <iostream>
#include <ostream>
#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

namespace Stella {

    void typecheckProgram(Program* program);

    void typecheck(Expr* expr, Type* type);

    Type* infer(Expr* expr);

} // namespace Stella

namespace TypeCheck {
    const std::string ERROR_UNDEFINED_VARIABLE = "ERROR_UNDEFINED_VARIABLE";
    const std::string ERROR_UNDEFINED_TYPE_VARIABLE = "ERROR_UNDEFINED_TYPE_VARIABLE";
    const std::string ERROR_MISSING_MAIN = "ERROR_MISSING_MAIN";

    const std::string ERROR_NOT_A_FUNCTION = "ERROR_NOT_A_FUNCTION";
    const std::string ERROR_NOT_A_TUPLE = "ERROR_NOT_A_TUPLE";
    const std::string ERROR_NOT_A_LIST = "ERROR_NOT_A_LIST";
    const std::string ERROR_NOT_A_REFERENCE = "ERROR_NOT_A_REFERENCE";
    const std::string ERROR_NOT_A_RECORD = "ERROR_NOT_A_RECORD";
    const std::string ERROR_NOT_A_GENERIC_FUNCTION = "ERROR_NOT_A_GENERIC_FUNCTION";

    const std::string ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION = "ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION";
    const std::string ERROR_UNEXPECTED_TYPE_FOR_PARAMETER = "ERROR_UNEXPECTED_TYPE_FOR_PARAMETER";
    const std::string ERROR_UNEXPECTED_LAMBDA = "ERROR_UNEXPECTED_LAMBDA";
    const std::string ERROR_UNEXPECTED_NUMBER_OF_PARAMETERS_IN_LAMBDA = "ERROR_UNEXPECTED_NUMBER_OF_PARAMETERS_IN_LAMBDA";
    const std::string ERROR_UNEXPECTED_TUPLE_LENGTH = "ERROR_UNEXPECTED_TUPLE_LENGTH";
    const std::string ERROR_UNEXPECTED_LIST = "ERROR_UNEXPECTED_LIST";
    const std::string ERROR_UNEXPECTED_INJECTION = "ERROR_UNEXPECTED_INJECTION";
    const std::string ERROR_UNEXPECTED_PATTERN_FOR_TYPE = "ERROR_UNEXPECTED_PATTERN_FOR_TYPE";
    const std::string ERROR_UNEXPECTED_MEMORY_ADDRESS = "ERROR_UNEXPECTED_MEMORY_ADDRESS";
    const std::string ERROR_UNEXPECTED_TUPLE = "ERROR_UNEXPECTED_TUPLE";
    const std::string ERROR_UNEXPECTED_RECORD_FIELDS = "ERROR_UNEXPECTED_RECORD_FIELDS";
    const std::string ERROR_UNEXPECTED_RECORD = "ERROR_UNEXPECTED_RECORD";
    const std::string ERROR_UNEXPECTED_FIELD_ACCESS = "ERROR_UNEXPECTED_FIELD_ACCESS";
    const std::string ERROR_UNEXPECTED_SUBTYPE = "ERROR_UNEXPECTED_SUBTYPE";
    const std::string ERROR_UNEXPECTED_VARIANT = "ERROR_UNEXPECTED_VARIANT";
    const std::string ERROR_UNEXPECTED_VARIANT_LABEL = "ERROR_UNEXPECTED_VARIANT_LABEL";

    const std::string ERROR_INCORRECT_ARITY_OF_MAIN = "ERROR_INCORRECT_ARITY_OF_MAIN";
    const std::string ERROR_INCORRECT_NUMBER_OF_ARGUMENTS = "ERROR_INCORRECT_NUMBER_OF_ARGUMENTS";
    const std::string ERROR_INCORRECT_TYPE_OF_MAIN = "ERROR_INCORRECT_TYPE_OF_MAIN";
    const std::string ERROR_INCORRECT_NUMBER_OF_TYPE_ARGUMENTS = "ERROR_INCORRECT_NUMBER_OF_TYPE_ARGUMENTS";

    const std::string ERROR_ILLEGAL_EMPTY_MATCHING = "ERROR_ILLEGAL_EMPTY_MATCHING";
    const std::string ERROR_ILLEGAL_NEGATIVE_LITERAL = "ERROR_ILLEGAL_NEGATIVE_LITERAL";

    const std::string ERROR_TUPLE_INDEX_OUT_OF_BOUNDS = "ERROR_TUPLE_INDEX_OUT_OF_BOUNDS";

    const std::string ERROR_AMBIGUOUS_SUM_TYPE = "ERROR_AMBIGUOUS_SUM_TYPE";
    const std::string ERROR_AMBIGUOUS_LIST_TYPE = "ERROR_AMBIGUOUS_LIST_TYPE";
    const std::string ERROR_AMBIGUOUS_VARIANT_TYPE = "ERROR_AMBIGUOUS_VARIANT_TYPE";
    const std::string ERROR_AMBIGUOUS_THROW_TYPE = "ERROR_AMBIGUOUS_THROW_TYPE";
    const std::string ERROR_AMBIGUOUS_REFERENCE_TYPE = "ERROR_AMBIGUOUS_REFERENCE_TYPE";
    const std::string ERROR_AMBIGUOUS_PANIC_TYPE = "ERROR_AMBIGUOUS_PANIC_TYPE";

    const std::string ERROR_NONEXHAUSTIVE_MATCH_PATTERNS = "ERROR_NONEXHAUSTIVE_MATCH_PATTERNS";
    const std::string ERROR_EXCEPTION_TYPE_NOT_DECLARED = "ERROR_EXCEPTION_TYPE_NOT_DECLARED";
    const std::string ERROR_MISSING_RECORD_FIELDS = "ERROR_MISSING_RECORD_FIELDS";
    const std::string ERROR_DUPLICATE_RECORD_FIELDS = "ERROR_DUPLICATE_RECORD_FIELDS";
    const std::string ERROR_OCCURS_CHECK_INFINITE_TYPE = "ERROR_OCCURS_CHECK_INFINITE_TYPE";
}

namespace TypeCheck {
    class Type {
    public:
        bool isAscripted = false;

        explicit Type() = default;
        virtual bool IsPrimitiveType() = 0;
        virtual std::shared_ptr<Type> Clone() = 0;
        virtual bool ContainsTypeVar(const int typeVarId) = 0;
        virtual bool MatchesTypeVar(std::shared_ptr<Type> otherType) = 0;
    };

    class Unknown: public Type {
    public:
        explicit Unknown() = default;
        bool IsPrimitiveType() override {
            return false;
        }
        bool ContainsTypeVar(const int typeVarId) override {
            return false;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            return true;
        }

        std::shared_ptr<Type> Clone() override {
            return std::make_shared<Unknown>();
        }
    };

    const int AUTO_ANY = -1;
    const int AUTO_UPDATE_SPEC = -2;
    const int AUTO_IGNORE = -3;
    const int SPEC_LEVEL_DISABLED = -4;

    inline int autoTypeCounter = 0;
    inline int currentSpecLevel = SPEC_LEVEL_DISABLED;

    class TypeAuto: public Type {
    public:
        int typeId;
        int specLevel;
        explicit TypeAuto() {
            typeId = autoTypeCounter++;
            specLevel = 0;
        };
        explicit TypeAuto(int definedType, int specLevel) {
            typeId = definedType;
            specLevel = specLevel;
        };
        explicit TypeAuto(int definedType) {
            typeId = definedType;
            specLevel = 0;
        };
        bool IsPrimitiveType() override {
            return false;
        }
        bool ContainsTypeVar(const int typeVarId) override {
            if (typeVarId == AUTO_ANY) {
                return true;
            }

            if (typeVarId == AUTO_IGNORE) {
                return false;
            }

            if (typeVarId == AUTO_UPDATE_SPEC) {
                this->specLevel = currentSpecLevel;
                return false;
            }

            if (currentSpecLevel != SPEC_LEVEL_DISABLED && currentSpecLevel >= 0) {
                if (this->typeId == typeVarId) {
                    this->specLevel = currentSpecLevel;
                }

                return false;
            }

            return this->typeId == typeVarId;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto otherTypeVar = std::dynamic_pointer_cast<TypeAuto>(otherType);
            if (!otherTypeVar) {
                return false;
            }

            return this->typeId == otherTypeVar->typeId;
        }

        std::shared_ptr<Type> Clone() override {
            auto newTypeVar = std::make_shared<TypeAuto>(this->typeId);
            newTypeVar->specLevel = this->specLevel;

            return newTypeVar;
        }
    };

    class Extremum: public Type {
    public:
        bool IsPrimitiveType() override {
            return false;
        }
        bool ContainsTypeVar(const int typeVarId) override {
            return false;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            return true;
        }
    };

    class Top: public Extremum {
    public:
        explicit Top() = default;
        std::shared_ptr<Type> Clone() override {
            return std::make_shared<Top>();
        }
    };

    class Bottom: public Extremum {
    public:
        explicit Bottom() = default;
        std::shared_ptr<Type> Clone() override {
            return std::make_shared<Bottom>();
        }
    };

    class Primitive: public Type {
    public:
        bool IsPrimitiveType() override {
            return true;
        }
        bool ContainsTypeVar(const int typeVarId) override {
            return false;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            return true;
        }
    };

    class Nat: public Primitive {
    public:
        explicit Nat() = default;
        std::shared_ptr<Type> Clone() override {
            return std::make_shared<Nat>();
        }
    };

    class Bool: public Primitive {
    public:
        explicit Bool() = default;
        std::shared_ptr<Type> Clone() override {
            return std::make_shared<Bool>();
        }
    };

    class Unit: public Type {
    public:
        explicit Unit() = default;
        bool IsPrimitiveType() override {
            return true;
        }
        bool ContainsTypeVar(const int typeVarId) override {
            return false;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            return true;
        }
        std::shared_ptr<Type> Clone() override {
            return std::make_shared<Unit>();
        }
    };

    class Function: public Type {
    public:
        std::vector<std::shared_ptr<Type>> parameterTypes;
        std::shared_ptr<Type> returnType;
        bool lambdaType = false;
        bool isInitLambdaType = false;
        bool genericType = false;
        explicit Function() {
            returnType = std::make_shared<Unknown>();
            lambdaType = false;
            isInitLambdaType = false;
            genericType = false;
        };
        explicit Function(std::shared_ptr<Type> arg, std::shared_ptr<Type> ret)
            : returnType(ret)
        {
            parameterTypes.push_back(arg);
            lambdaType = false;
            isInitLambdaType = false;
            genericType = false;
        }
        explicit Function(std::shared_ptr<Type> arg, bool is_generic_)
            : genericType(is_generic_)
        {
            parameterTypes.push_back(arg);
            returnType = std::make_shared<Unknown>();
        }
        bool IsPrimitiveType() override {
            return false;
        }
        bool ContainsTypeVar(const int typeVarId) override {
            for (auto& arg : parameterTypes) {
                if (arg->ContainsTypeVar(typeVarId)) {
                    return true;
                }
            }

            if (returnType->ContainsTypeVar(typeVarId)) {
                return true;
            }

            return false;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto another_func = std::dynamic_pointer_cast<Function>(otherType);
            if (!another_func) {
                return false;
            }

            if (this->parameterTypes.size() != another_func->parameterTypes.size()) {
                return false;
            }

            for (int i = 0; i < this->parameterTypes.size(); i++) {
                if (!this->parameterTypes[i]->MatchesTypeVar(another_func->parameterTypes[i])) {
                    return false;
                }
            }

            if (!returnType->MatchesTypeVar(another_func->returnType)) {
                return false;
            }

            return true;
        }
        std::shared_ptr<Type> Clone() override {
            auto new_func = std::make_shared<Function>();
            for (auto& arg : this->parameterTypes) {
                new_func->parameterTypes.push_back(arg->Clone());
            }

            new_func->returnType = this->returnType->Clone();
            return new_func;
        }
    };

    class Forall: public Type {
    public:
        std::shared_ptr<Type> internal;
        std::vector<std::shared_ptr<TypeAuto>> universalVariables;

        explicit Forall() = default;
        explicit Forall(std::shared_ptr<Type> type_)
            : internal(type_)
        {
        }

        std::shared_ptr<Type> Clone() override {
            auto newForall = std::make_shared<Forall>();
            newForall->internal = this->internal->Clone();

            for (auto& univ : universalVariables) {
                newForall->universalVariables.push_back(std::dynamic_pointer_cast<TypeAuto>(univ->Clone()));
            }

            return newForall;
        }

        bool IsPrimitiveType() override {
            return false;
        }
        bool ContainsTypeVar(const int typeVarId) override {
            for (auto& univ : universalVariables) {
                univ->ContainsTypeVar(typeVarId);
            }

            return internal->ContainsTypeVar(typeVarId);
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto another_forall = std::dynamic_pointer_cast<Forall>(otherType);
            if (!another_forall) {
                return false;
            }
            return this->internal->MatchesTypeVar(another_forall->internal);
        }
    };

    class Tuple: public Type {
    public:
        std::vector<std::shared_ptr<Type>> elementTypes;
        explicit Tuple() = default;
        explicit Tuple(std::vector<std::shared_ptr<Type>>& items)
            : elementTypes(items)
        {
        }
        bool is_pair() {
            return elementTypes.size() == 2;
        }
        bool IsPrimitiveType() override {
            return false;
        }
        int size() {
            return elementTypes.size();
        }
        bool ContainsTypeVar(const int typeVarId) override {
            for (auto& item : elementTypes) {
                if (item->ContainsTypeVar(typeVarId)) {
                    return true;
                }
            }

            return false;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto another_tuple = std::dynamic_pointer_cast<Tuple>(otherType);
            if (!another_tuple) {
                return false;
            }

            if (this->elementTypes.size() != another_tuple->elementTypes.size()) {
                return false;
            }

            for (int i = 0; i < this->elementTypes.size(); i++) {
                if (!this->elementTypes[i]->MatchesTypeVar(another_tuple->elementTypes[i])) {
                    return false;
                }
            }

            return true;
        }
        std::shared_ptr<Type> Clone() override {
            auto newReference = std::make_shared<Tuple>();
            for (auto& ent : this->elementTypes) {
                newReference->elementTypes.push_back(ent->Clone());
            }
            return newReference;
        }
    };

    class Record: public Type {
    private:
        std::unordered_map<std::string, bool> fieldMetadata;

    public:
        std::unordered_map<std::string, std::shared_ptr<Type>> fieldTypes;
        explicit Record() = default;
        explicit Record(std::vector<std::shared_ptr<Type>>& types, std::vector<std::string>& names) {
            if (types.size() != names.size()) {
                std::cout << "Record error: cannot initialize map, sizes of types and names: " << types.size() << " " << names.size() << "\n";
                exit(1);
            }

            for (int i = 0; i < types.size(); i++) {
                auto type_ = types[i];
                auto name_ = names[i];

                fieldTypes[name_] = type_;
                fieldMetadata[name_] = true;
            }
        }
        explicit Record(std::shared_ptr<Record> another_rec) {
            for (auto& p : another_rec->fieldTypes) {
                this->fieldTypes[p.first] = p.second;
                fieldMetadata[p.first] = false;
            }
        }

        bool ContainsTypeVar(const int typeVarId) override {
            for (auto& p : fieldTypes) {
                if (p.second->ContainsTypeVar(typeVarId)) {
                    return true;
                }
            }

            return false;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto recordType = std::dynamic_pointer_cast<Record>(otherType);
            if (!recordType) {
                return false;
            }

            for (auto& p : fieldTypes) {
                if (!p.second->MatchesTypeVar(recordType->access(p.first))) {
                    return false;
                }
            }

            return true;
        }

        bool IsPrimitiveType() override {
            return false;
        }
        int size() {
            return fieldTypes.size();
        }
        bool HasField(std::string field) {
            return fieldTypes.find(field) != fieldTypes.end();
        }
        std::shared_ptr<Type> access(std::string field) {
            if (HasField(field)) {
                return fieldTypes[field];
            } else {
                return nullptr;
            }
        }
        void AddField(std::string bindingName, std::shared_ptr<Type> field_type) {
            if (HasField(bindingName)) {
                std::cout << ERROR_DUPLICATE_RECORD_FIELDS << "\n";
                exit(1);
            }

            fieldTypes[bindingName] = field_type;
            fieldMetadata[bindingName] = true;
        }

        void ClearMarks() {
            for (auto& exst : fieldMetadata) {
                exst.second = false;
            }
        }
        bool EachFieldExists() {
            for (auto& exst : fieldMetadata) {
                if (!exst.second) {
                    return false;
                }
            }

            return true;
        }
        void PrintExst() {
            std::cout << "{";
            int tmp_counter = 0;
            for (auto& p : fieldMetadata) {
                tmp_counter++;
                std::cout << p.first << " : " << (p.second ? "true" : "false");

                if (tmp_counter != fieldTypes.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << "}\n";
        }
        void field_exst(std::string& bindingName) {
            fieldMetadata[bindingName] = true;
        }
        std::shared_ptr<Type> Clone() override {
            auto newReference = std::make_shared<Record>();

            newReference->fieldMetadata = this->fieldMetadata;
            for (auto& p : fieldTypes) {
                newReference->AddField(p.first, p.second->Clone());
            }

            return newReference;
        }
    };

    class Sum: public Type {
    public:
        std::shared_ptr<Type> left;
        std::shared_ptr<Type> right;
        explicit Sum() = default;
        explicit Sum(std::shared_ptr<Type> left_, std::shared_ptr<Type> right_) {
            this->left = left_;
            this->right = right_;
        }
        explicit Sum(bool is_right, std::shared_ptr<Type> known_type) {
            if (is_right) {
                this->right = known_type;
            } else {
                this->left = known_type;
            }
        }
        bool IsPrimitiveType() override {
            return false;
        }

        bool ContainsTypeVar(const int typeVarId) override {
            bool l = false;
            bool r = false;
            if (left) {
                l = left->ContainsTypeVar(typeVarId);
            }
            if (right) {
                r = right->ContainsTypeVar(typeVarId);
            }

            return r || l;
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto another_sum = std::dynamic_pointer_cast<Sum>(otherType);
            if (!another_sum) {
                return false;
            }

            bool l = true;
            bool r = true;
            if (left && another_sum->left) {
                l = left->MatchesTypeVar(another_sum->left);
            }
            if (right && another_sum->right) {
                r = right->MatchesTypeVar(another_sum->right);
            }

            return r && l;
        }

        bool IsInl() {
            return !!left;
        }
        bool IsInr() {
            return !!right;
        }
        bool IsFull() {
            return !!left && !!right;
        }
        std::shared_ptr<Type> Clone() override {
            auto newReference = std::make_shared<Sum>();

            newReference->left = this->left->Clone();
            newReference->right = this->right->Clone();

            return newReference;
        }
    };

    class List: public Type {
    public:
        std::shared_ptr<Type> currentInnerType;
        explicit List() = default;
        explicit List(std::shared_ptr<Type> init_type_)
            : currentInnerType(init_type_)
        {
        }
        explicit List(bool possible_AnyType) {
            currentInnerType = std::make_shared<Unknown>();
        }

        bool ContainsTypeVar(const int typeVarId) override {
            return currentInnerType->ContainsTypeVar(typeVarId);
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto another_list = std::dynamic_pointer_cast<List>(otherType);
            if (!another_list) {
                return false;
            }
            return this->currentInnerType->MatchesTypeVar(another_list->currentInnerType);
        }

        bool IsPrimitiveType() override {
            return false;
        }
        bool AnyType() {
            return std::dynamic_pointer_cast<Unknown>(currentInnerType) != nullptr;
        }
        std::shared_ptr<Type> Clone() override {
            auto newReference = std::make_shared<List>();
            newReference->currentInnerType = this->currentInnerType->Clone();
            return newReference;
        }
    };

    class Ref: public Type {
    public:
        std::shared_ptr<Type> dereferencedType;
        explicit Ref() = default;
        explicit Ref(std::shared_ptr<Type> type_)
            : dereferencedType(type_)
        {
        }
        bool IsPrimitiveType() override {
            return false;
        }

        bool ContainsTypeVar(const int typeVarId) override {
            return dereferencedType->ContainsTypeVar(typeVarId);
        }
        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto another_ref = std::dynamic_pointer_cast<Ref>(otherType);
            if (!another_ref) {
                return false;
            }
            return this->dereferencedType->MatchesTypeVar(another_ref->dereferencedType);
        }
        std::shared_ptr<Type> Clone() override {
            auto newReference = std::make_shared<Ref>();
            newReference->dereferencedType = this->dereferencedType->Clone();
            return newReference;
        }
    };

    class Variant: public Type {
    private:
        std::unordered_map<std::string, bool> fieldMetadata;

    public:
        std::unordered_map<std::string, std::shared_ptr<Type>> variantTypes;
        bool ambiguous = false;

        explicit Variant() = default;
        explicit Variant(std::vector<std::shared_ptr<Type>>& types, std::vector<std::string>& labels) {
            if (types.size() != labels.size()) {
                std::cout << "Variant error: cannot initialize map, sizes of types and labels: " << types.size() << " " << labels.size() << "\n";
                exit(1);
            }

            for (int i = 0; i < types.size(); i++) {
                auto type_ = types[i];
                auto label_ = labels[i];

                variantTypes[label_] = type_;
                fieldMetadata[label_] = false;
            }
        }
        explicit Variant(std::string& label_, std::shared_ptr<Type> type_) {
            variantTypes[label_] = type_;
            fieldMetadata[label_] = false;

            ambiguous = true;
        }

        bool ContainsTypeVar(const int typeVarId) override {
            for (auto& p : variantTypes) {
                if (p.second->ContainsTypeVar(typeVarId)) {
                    return true;
                }
            }

            return false;
        }

        bool MatchesTypeVar(std::shared_ptr<Type> otherType) override {
            auto another_var = std::dynamic_pointer_cast<Variant>(otherType);
            if (!another_var) {
                return false;
            }

            for (auto& p : variantTypes) {
                if (!p.second->MatchesTypeVar(another_var->access(p.first))) {
                    return false;
                }
            }

            return true;
        }

        bool IsPrimitiveType() override {
            return false;
        }
        bool HasVariant(std::string label) {
            return variantTypes.find(label) != variantTypes.end();
        }
        std::shared_ptr<Type> access(std::string label) {
            if (HasVariant(label)) {
                return variantTypes[label];
            } else {
                return nullptr;
            }
        }

        int size() {
            return variantTypes.size();
        }

        void ClearMarks() {
            for (auto& exst : fieldMetadata) {
                exst.second = false;
            }
        }
        bool EachFieldExists() {
            for (auto& exst : fieldMetadata) {
                if (!exst.second) {
                    return false;
                }
            }

            return true;
        }
        void PrintExst() {
            std::cout << "{";
            int tmp_counter = 0;
            for (auto& p : fieldMetadata) {
                tmp_counter++;
                std::cout << p.first << " : " << (p.second ? "true" : "false");

                if (tmp_counter != variantTypes.size()) {
                    std::cout << ", ";
                }
            }
            std::cout << "}\n";
        }
        void match_label(std::string& bindingName) {
            fieldMetadata[bindingName] = true;
        }
        std::shared_ptr<Type> Clone() override {
            auto newReference = std::make_shared<Variant>();

            newReference->fieldMetadata = this->fieldMetadata;
            for (auto& p : variantTypes) {
                newReference->variantTypes[p.first] = p.second->Clone();
            }

            return newReference;
        }
    };

    class Env {
    private:
        class EnvItem {
        public:
            int indentationLevel;
            bool isLValue = false;
            std::shared_ptr<Type> lastType;
            std::string currentScopeName;
            std::shared_ptr<Type> patternMatchInitialType;
            std::shared_ptr<Type> currentPatternMatchType;
            int lastIntegerValue;

            std::shared_ptr<Type> item;
            std::unordered_map<std::string, std::shared_ptr<EnvItem>> map;
            explicit EnvItem()
                : indentationLevel(0)
                , isLValue(false)
            {};
            explicit EnvItem(std::shared_ptr<Type> item_)
                : item(item_)
                , indentationLevel(0)
                , isLValue(false)
            {};

        };

        class ConstraintsScope {
        public:
            explicit ConstraintsScope()
            {
            }

            class Constraint {
            public:
                std::shared_ptr<Type> left;
                std::shared_ptr<Type> right;
                bool trivial = false;
                bool reversed = false;

                explicit Constraint(std::shared_ptr<Type> from, std::shared_ptr<Type> to) {
                    this->left = from;
                    this->right = to;
                }
                explicit Constraint()
                    : trivial(true)
                {
                }
            };

            std::vector<std::unordered_map<int, std::vector<std::shared_ptr<Type>>>> constraints = {{}};
            std::vector<std::unordered_map<int, std::vector<std::shared_ptr<Type>>>> typeVariableDefinitions = {{}};

            void define(std::shared_ptr<TypeAuto> univ, std::shared_ptr<Type> def, int specLevel) {
                define(Constraint(univ, def), AUTO_IGNORE, specLevel);
            }
            void define(Constraint ctr) {
                define(ctr, AUTO_ANY, 0);
            }
            void define(Constraint ctr, int FRESH_STATUS, int specLevel) {
                if (auto typeVar = std::dynamic_pointer_cast<TypeAuto>(ctr.left)) {
                    ctr.reversed = false;

                    if (!ctr.right->ContainsTypeVar(FRESH_STATUS)) {
                        if (!IsTypeVariableDefined(typeVar->typeId, specLevel)) {
                            typeVariableDefinitions[specLevel][typeVar->typeId] = {};
                        }

                        typeVariableDefinitions[specLevel][typeVar->typeId].push_back(ctr.right);

                    } else {
                        if (!HasTypeConstraints(typeVar->typeId)) {
                            constraints[specLevel][typeVar->typeId] = {};
                        }

                        constraints[specLevel][typeVar->typeId].push_back(ctr.right);
                    }
                } else {
                    if (ctr.reversed) {
                        std::cout << "ConstraintScope error: recursion in define()\n";
                        exit(1);
                    }

                    auto rev_ctr = Constraint(ctr.right, ctr.left);
                    rev_ctr.reversed = true;
                    define(rev_ctr);
                }
            }

            void UpdateConstraits(int typeId, std::vector<std::shared_ptr<Type>>& new_constraits) {
                UpdateConstraits(typeId, new_constraits, 0);
            }
            void UpdateConstraits(int typeId, std::vector<std::shared_ptr<Type>>& new_constraits, int specLevel) {
                if (!HasTypeConstraints(typeId)) {
                    std::cout << "ConstraintScope error: no constraits in UpdateConstraits()\n";
                    exit(1);
                }

                constraints[specLevel][typeId] = new_constraits;
            }

            Constraint ValidateConstraits(Constraint init_ctr) {
                if (auto typeVar = std::dynamic_pointer_cast<TypeAuto>(init_ctr.left)) {
                    init_ctr.reversed = false;

                    if (init_ctr.right->ContainsTypeVar(typeVar->typeId)) {
                        if (std::dynamic_pointer_cast<TypeAuto>(init_ctr.right)) {
                            return Constraint();
                        }

                        if (IsTypeVariableDefined(typeVar->typeId)) {
                            std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                            exit(1);
                        }

                        std::cout << ERROR_OCCURS_CHECK_INFINITE_TYPE << "\n";
                        exit(1);
                    }

                    return init_ctr;
                } else {
                    if (init_ctr.reversed) {
                        std::cout << "ConstraintScope error: recursion in ValidateConstraits()\n";
                        exit(1);
                    }

                    auto rev_ctr = Constraint(init_ctr.right, init_ctr.left);
                    rev_ctr.reversed = true;
                    return ValidateConstraits(rev_ctr);
                }
            }

            bool IsTypeVariableDefined(int typeId) {
                return IsTypeVariableDefined(typeId, 0);
            }
            bool IsTypeVariableDefined(int typeId, int specLevel) {
                if (typeVariableDefinitions.size() <= specLevel) {
                    std::cout << "ConstraintScope error: typeVariableDefinitions is too small to extract " << specLevel << "\n";
                    exit(1);
                }

                return typeVariableDefinitions[specLevel].find(typeId) != typeVariableDefinitions[specLevel].end();
            }

            bool HasTypeConstraints(int typeId) {
                return HasTypeConstraints(typeId, 0);
            }
            bool HasTypeConstraints(int typeId, int specLevel) {
                if (constraints.size() <= specLevel) {
                    std::cout << "ConstraintScope error: constraints is too small to extract " << specLevel << "\n";
                    exit(1);
                }

                return constraints[specLevel].find(typeId) != constraints[specLevel].end();
            }

            void CreateTypeConstraint(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
                auto ctr = Constraint(actual, expected);
                ctr = ValidateConstraits(ctr);

                if (ctr.trivial) {
                    return;
                }

                define(ctr);
            }

            std::vector<std::shared_ptr<Type>> GetDefinitions(int typeId) {
                return GetDefinitions(typeId, 0);
            }
            std::vector<std::shared_ptr<Type>> GetDefinitions(int typeId, int specLevel) {
                if (!IsTypeVariableDefined(typeId, specLevel)) {
                    if (specLevel == 0) {
                        return std::vector<std::shared_ptr<Type>>();
                    }

                    return GetDefinitions(typeId, 0);
                }

                if (specLevel == 0 || !IsTypeVariableDefined(typeId, 0)) {
                    return typeVariableDefinitions[specLevel][typeId];
                }

                auto def_zero = typeVariableDefinitions[0][typeId];
                auto def_spec = typeVariableDefinitions[specLevel][typeId];

                def_spec.insert(def_spec.end(), def_zero.begin(), def_zero.begin());
                return def_zero;
            }

            std::vector<std::shared_ptr<Type>> GetConstraints(int typeId) {
                return GetConstraints(typeId, 0);
            }
            std::vector<std::shared_ptr<Type>> GetConstraints(int typeId, int specLevel) {
                if (!HasTypeConstraints(typeId)) {
                    if (specLevel == 0) {
                        return std::vector<std::shared_ptr<Type>>();
                    }

                    return GetConstraints(typeId, 0);
                }

                if (specLevel == 0 || !HasTypeConstraints(typeId, 0)) {
                    return constraints[specLevel][typeId];
                }

                auto ctr_zero = constraints[0][typeId];
                auto ctr_spec = constraints[specLevel][typeId];

                ctr_zero.insert(ctr_zero.end(), ctr_zero.begin(), ctr_spec.end());
                return ctr_zero;
            }

            void FoldDefinitions(int typeId) {
                FoldDefinitions(typeId, 0);
            }
            void FoldDefinitions(int typeId, int specLevel) {
                if (!IsTypeVariableDefined(typeId, specLevel)) {
                    return;
                }

                if (typeVariableDefinitions[specLevel][typeId].size() == 1) {
                    return;
                }

                typeVariableDefinitions[specLevel][typeId].resize(1);
            }

            void FoldConstraints(int typeId) {
                FoldConstraints(typeId, 0);
            }
            void FoldConstraints(int typeId, int specLevel) {
                if (!HasTypeConstraints(typeId)) {
                    return;
                }

                auto constraits = GetConstraints(typeId, specLevel);
                if (constraits.size() == 1) {
                    return;
                }

                for (auto it1 = constraits.begin(); it1 != constraits.end(); ++it1) {
                    for (auto it2 = it1 + 1; it2 != constraits.end();) {
                        if ((*it1)->MatchesTypeVar(*it2)) {
                            it2 = constraits.erase(it2);
                        } else {
                            ++it2;
                        }
                    }
                }

                UpdateConstraits(typeId, constraits);
            }

            void DefineViaConstraints(std::shared_ptr<TypeAuto> typeVar) {
                auto constraits = GetConstraints(typeVar->typeId);
                for (auto& ctr : constraits) {
                    if (auto typeVarConstraits = std::dynamic_pointer_cast<TypeAuto>(ctr)) {
                        if (IsTypeVariableDefined(typeVarConstraits->typeId)) {
                            auto defs = GetDefinitions(typeVarConstraits->typeId);
                            if (defs.empty()) {
                                continue;
                            }

                            define(Constraint(typeVar, defs[0]));
                            return;
                        }
                    }
                }
            }

            void RemoveCyclicConstraints(int typeId, int rm_idx, int init_idx) {
                if (!HasTypeConstraints(typeId)) {
                    return;
                }

                auto constraits = GetConstraints(typeId);

                for (auto it = constraits.begin(); it != constraits.end();) {
                    auto ctr = *it;
                    auto typeVarConstraits = std::dynamic_pointer_cast<TypeAuto>(ctr);

                    if (!typeVarConstraits) {
                        ++it;
                        continue;
                    }

                    if (typeVarConstraits->typeId == typeId || typeVarConstraits->typeId == rm_idx || typeVarConstraits->typeId == init_idx) {
                        it = constraits.erase(it);
                    } else {
                        ++it;
                    }
                }

                UpdateConstraits(typeId, constraits);

                for (auto& ctr : constraits) {
                    auto typeVarConstraits = std::dynamic_pointer_cast<TypeAuto>(ctr);
                    if (!typeVarConstraits) {
                        continue;
                    }
                    RemoveCyclicConstraints(typeVarConstraits->typeId, typeId, init_idx);
                }
            }
        };

        enum class ListFunctionType {
            HEAD,
            TAIL,
            ISEMPTY,

            UNKNOWN
        };
        enum class RecordFieldError {
            NO,
            MISSING,
            UNEXP
        };

        std::shared_ptr<EnvItem> symbolBindings;
        std::vector<std::string> contextPath;

        std::shared_ptr<ConstraintsScope> typeConstraints;

        std::shared_ptr<Type> exceptionType;

        std::vector<std::string> callTrace;
        std::vector<std::shared_ptr<Type>> typeEvaluationStack;
        std::vector<std::pair<bool, bool>> patternMatchFlags;
        std::vector<std::shared_ptr<Type>> typeInferenceBuffer;
        std::vector<int> multiInferenceMarkers;
        std::vector<std::string> recordFieldsBuffer;
        std::vector<int> specializationMarkers;
        std::vector<std::string> universalQuantifiers;
        std::vector<std::vector<std::shared_ptr<Type>>> polyTypeDefinitions;

        int anonymousFunctionId = 0;
        int patternMatchId = 0;
        int sequenceFunctionId = 0;
        int localBindingId = 0;
        int universalQuantifierId = 0;
        bool hasParameterError = false;
        bool hasArityMismatch = false;
        bool hasSequenceError = false;
        RecordFieldError fieldValidationState = RecordFieldError::NO;

        std::shared_ptr<EnvItem> Navigate() {
            auto currentCtx = symbolBindings;
            for (auto& entity : contextPath) {
                if (currentCtx->map.find(entity) == currentCtx->map.end()) {
                    return nullptr;
                }
                currentCtx = currentCtx->map[entity];
            }

            return currentCtx;
        }
        std::shared_ptr<Function> ExtractFunctionFromContext() {
            auto currentCtx = Navigate();
            auto function = std::dynamic_pointer_cast<Function>(currentCtx->item);

            if (universalTypes && !function) {
                auto forall = std::dynamic_pointer_cast<Forall>(currentCtx->item);
                if (!forall) {
                    std::cout << "TypeSystem Error: Expected generic function type\n";
                    exit(1);
                }

                function = std::dynamic_pointer_cast<Function>(forall->internal);
            }

            if (!function) {
                std::cout << "TypeSystem Error: Context item is not a function\n";
                exit(1);
            }

            return function;
        }
        bool IsInvalidFunction(std::shared_ptr<Function> func) {
            return !func || !func->returnType || IsTypeUndefined(func->returnType);
        }
        void MarkFirstPatternMatchRequirement() {
            if (patternMatchFlags.empty()) {
                std::cout << "TypeSystem Error: Empty pattern match stack\n";
                exit(1);
            }

            auto [firstFlag, secondFlag] = patternMatchFlags.back();
            patternMatchFlags.pop_back();
            patternMatchFlags.emplace_back(true, secondFlag);
        }

        void MarkSecondPatternMatchRequirement() {
            if (patternMatchFlags.empty()) {
                std::cerr << "TypeSystem Error: Empty pattern match stack\n";
                exit(EXIT_FAILURE);
            }

            auto [firstFlag, secondFlag] = patternMatchFlags.back();
            patternMatchFlags.pop_back();
            patternMatchFlags.emplace_back(firstFlag, true);
        }

        template <typename T>
        std::vector<T> GetSubstack(int checkpointIndex, std::vector<T>& stack) {
            if (checkpointIndex < 0 || checkpointIndex > static_cast<int>(stack.size())) {
                std::cout << "TypeSystem Error: Invalid stack checkpoint index " << checkpointIndex << " for stack of size " << stack.size() << "\n";
                exit(1);
            }

            auto sliceStart = stack.begin() + checkpointIndex;
            std::vector<T> substack(sliceStart, stack.end());
            stack.erase(sliceStart, stack.end());
            
            return substack;
        }

        template <typename T>
        void VerifyTypeAnnotation(std::shared_ptr<Type> actualType, std::shared_ptr<Type> expectedType, const std::string& errorMessage) {
            if (!actualType->isAscripted) {
                auto item = std::dynamic_pointer_cast<T>(actualType);
                auto another_item = std::dynamic_pointer_cast<T>(expectedType);
                if (!item || !!another_item) {
                    return;
                }

                std::cout << errorMessage << "\n";
                exit(1);
            }
        }

        template <typename T>
        bool IsTypeTemplate(std::shared_ptr<Type> entity) {
            return std::dynamic_pointer_cast<T>(entity) != nullptr;
        }

        void ClearLambdaFlag(std::shared_ptr<Type> func_) {
            auto func = std::dynamic_pointer_cast<Function>(func_);
            if (func) {
                func->lambdaType = false;
            }
        }

        std::shared_ptr<Type> GetInferredSumType() {
            auto inferredType = GetCurrentInferredType();

            if (IsUnknown(inferredType)) {
                if (ambiguousTypeAsBottom || typeReconstruction) {
                    return std::make_shared<Unknown>();
                }

                std::cout << ERROR_AMBIGUOUS_SUM_TYPE << "\n";
                exit(1);
            }

            auto sum = std::dynamic_pointer_cast<Sum>(inferredType);
            if (typeReconstruction && IsTypeVariable(inferredType)) {
                auto typeVar = std::dynamic_pointer_cast<TypeAuto>(inferredType);
                auto sumWithTypeVariables = CreateSumWithTypeVariables();

                if (!TypesMatch(typeVar, sumWithTypeVariables)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                sum = sumWithTypeVariables;
            }

            if (!sum) {
                if (typeReconstruction) {
                    ReconstructionError();
                }

                std::cout << ERROR_UNEXPECTED_INJECTION << "\n";
                exit(1);
            }

            return sum;
        }

        std::shared_ptr<Type> InferInjectionType(std::function<std::shared_ptr<Type>(std::shared_ptr<Sum>)> accessor) {
            auto inferredSumType = GetInferredSumType();

            if (!ambiguousTypeAsBottom) {
                auto sum = std::dynamic_pointer_cast<Sum>(inferredSumType);
                if (!sum) {
                    std::cout << "TypeSystem Error: impossible to use sum type (InferInjectionType)\n";
                    exit(1);
                }

                auto accessed = accessor(sum);

                UpdateLastType(accessed);
                return accessed;
            } else {
                UpdateLastType(inferredSumType);
                return inferredSumType;
            }
        }

        void ProcessInjectionMatch(
            std::function<bool(std::shared_ptr<Sum>)> verifier,
            std::function<std::shared_ptr<Type>(std::shared_ptr<Sum>)> accessor,
            std::string word) {
            auto currentCtx = Navigate();
            auto matchedType = currentCtx->currentPatternMatchType;

            std::shared_ptr<Sum> sum_item = std::dynamic_pointer_cast<Sum>(matchedType);
            if (typeReconstruction && IsTypeVariable(matchedType)) {
                sum_item = CreateSumWithTypeVariables();
                if (!TypesMatch(matchedType, sum_item)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }
            }

            if (!matchedType || !sum_item) {
                std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                exit(1);
            }

            if (!verifier(sum_item)) {
                std::cout << ERROR_AMBIGUOUS_SUM_TYPE << "\n";
                exit(1);
            }
            currentCtx->currentPatternMatchType = accessor(sum_item);

            if (IsFunctionType(currentCtx->currentPatternMatchType)) {
                ClearLambdaFlag(currentCtx->currentPatternMatchType);
            }
        }
        void ResolveInjectionType(std::shared_ptr<Sum> inl_inr) {
            std::shared_ptr<Type> replace;

            if (ambiguousTypeAsBottom) {
                replace = std::make_shared<Bottom>();
            } else if (typeReconstruction) {
                replace = std::make_shared<TypeAuto>();
            }

            if (inl_inr->IsInl()) {
                inl_inr->right = replace;
            } else {
                inl_inr->left = replace;
            }
        }

        bool IsEmptyListWithUnknownType(std::shared_ptr<Type> empty_lst_content) {
            if (!empty_lst_content) {
                return true;
            }

            if (IsUnknown(empty_lst_content)) {
                return true;
            }

            if (!IsListType(empty_lst_content)) {
                return false;
            }

            auto empty_lst = std::dynamic_pointer_cast<List>(empty_lst_content);
            if (!empty_lst) {
                std::cout << "TypeSystem Error: cannot cast to list (IsEmptyListWithUnknownType) ";
                exit(1);
            }

            return IsEmptyListWithUnknownType(empty_lst->currentInnerType);
        }

        bool IsNullReference(std::shared_ptr<Type> null_ref) {
            if (!null_ref) {
                return true;
            }

            if (IsUnknown(null_ref)) {
                return true;
            }

            if (!IsRefType(null_ref)) {
                return false;
            }

            auto refered = std::dynamic_pointer_cast<Ref>(null_ref);
            if (!refered) {
                std::cout << "TypeSystem Error: cannot cast to ref (IsNullReference) ";
                exit(1);
            }

            return IsNullReference(refered->dereferencedType);
        }

        void ValidateListOperation(std::shared_ptr<Type> listType, ListFunctionType operationType) {
            auto inferredListType = std::dynamic_pointer_cast<List>(GetCurrentInferredType());
            auto actualListType = std::dynamic_pointer_cast<List>(listType);

            std::shared_ptr<Type> resultType;

            if (typeReconstruction && IsTypeVariable(listType)) {
                actualListType = std::make_shared<List>(std::make_shared<TypeAuto>());

                if (!TypesMatch(listType, actualListType)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }
            }

            if (inferredListType && actualListType) {
                if (operationType == ListFunctionType::HEAD) {
                    resultType = actualListType->currentInnerType;
                } else if (operationType == ListFunctionType::TAIL) {
                    resultType = actualListType;
                } else if (operationType == ListFunctionType::ISEMPTY) {
                    resultType = std::make_shared<Bool>();
                } else {
                    resultType = std::make_shared<Unknown>();
                }

                resultType->isAscripted = listType->isAscripted;

                if (IsEmptyListWithUnknownType(resultType) && IsEmptyListWithUnknownType(resultType)) {
                    std::cout << ERROR_AMBIGUOUS_LIST_TYPE << "\n";
                    exit(1);
                }

                if (!TypesMatch(inferredListType, actualListType)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                if (!IsEmptyListWithUnknownType(resultType)) {
                    UpdateLastType(resultType);
                } else {
                    UpdateLastType(resultType);
                }
            } else {
                std::cout << ERROR_NOT_A_LIST << "\n";
                exit(1);
            }
        }

        std::shared_ptr<Tuple> CreateTypeVariableTuple() {
            int typeVariablesCount = 2;
            std::vector<std::shared_ptr<Type>> typeVariables(typeVariablesCount);

            for (int i = 0; i < typeVariablesCount; i++) {
                typeVariables[i] = std::make_shared<TypeAuto>();
            }

            auto newTuple = std::make_shared<Tuple>(typeVariables);
            if (!TypesMatch(GetCurrentInferredType(), newTuple)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            return newTuple;
        }
        std::shared_ptr<Ref> CreateReferenceWithTypeVariable() {
            return std::make_shared<Ref>(std::make_shared<TypeAuto>());
        }
        std::shared_ptr<Function> CreateFunctionWithTypeVariables() {
            return std::make_shared<Function>(
                std::make_shared<TypeAuto>(),
                std::make_shared<TypeAuto>());
        }
        std::shared_ptr<Sum> CreateSumWithTypeVariables() {
            return std::make_shared<Sum>(
                std::make_shared<TypeAuto>(),
                std::make_shared<TypeAuto>());
        }

        std::pair<bool, std::shared_ptr<Type>> ProcessTypeVariableEquation(
            std::shared_ptr<TypeAuto> typeVar,
            std::function<std::vector<std::shared_ptr<Type>>(int)> extract,
            const std::string word,
            std::shared_ptr<Type> verifier) {
            std::vector<std::shared_ptr<Type>> typeVarDefinitions = extract(typeVar->typeId);
            if (typeVarDefinitions.empty()) {
                return std::make_pair(true, nullptr);
            }

            if (!verifier) {
                for (int d = 0; d < typeVarDefinitions.size() - 1; d++) {
                    if (!TypesMatch(typeVarDefinitions[d], typeVarDefinitions[d + 1])) {
                        return std::make_pair(false, nullptr);
                    }
                }

                auto definition = typeVarDefinitions[0];
                return std::make_pair(true, definition);
            } else {
                for (auto& ctr : typeVarDefinitions) {
                    if (!TypesMatch(verifier, ctr)) {
                        return std::make_pair(false, nullptr);
                    }
                }

                return std::make_pair(true, nullptr);
            }
        }

        bool ProcessTypeEquation(std::shared_ptr<TypeAuto> typeVar) {
            // definitions
            auto [defSuccess, definition] = ProcessTypeVariableEquation(typeVar, [&](int typeId) { return typeConstraints->GetDefinitions(typeId); }, "Definitions", nullptr);

            if (!defSuccess) {
                return false;
            }

            if (definition) {
                typeConstraints->FoldDefinitions(typeVar->typeId);
            }

            typeConstraints->RemoveCyclicConstraints(typeVar->typeId, typeVar->typeId, typeVar->typeId);

            // constraints
            auto [ctrSuccess, _] = ProcessTypeVariableEquation(typeVar, [&](int typeId) { return typeConstraints->GetConstraints(typeId); }, "Constraints", definition);

            if (!universalTypes && !definition) {
                typeConstraints->DefineViaConstraints(typeVar);
            }

            typeConstraints->FoldConstraints(typeVar->typeId);

            return ctrSuccess;
        }

        bool ProcessUniversalTypeEquation(std::shared_ptr<TypeAuto> universalVar, std::shared_ptr<Type> otherType, int specLevel) {
            auto universalDefs = typeConstraints->GetDefinitions(universalVar->typeId, specLevel);

            if (universalDefs.empty() && IsTypeVariable(otherType)) {
                auto otherTypeVar = std::dynamic_pointer_cast<TypeAuto>(otherType);
                if (!otherTypeVar) {
                    std::cout << "TypeSystem Error: ProcessUniversalTypeEquation\n";
                    exit(1);
                }

                auto otherDefs = typeConstraints->GetDefinitions(otherTypeVar->typeId, otherTypeVar->specLevel);
                for (auto& def : otherDefs) {
                    if (auto typeVarDef = std::dynamic_pointer_cast<TypeAuto>(def)) {
                        if (UniversalTypesMatch(universalVar, typeVarDef)) {
                            return true;
                        }
                    }
                }
            }

            if (universalDefs.empty()) {
                return false;
            }

            for (auto& def : universalDefs) {
                if (!TypesMatch(otherType, def)) {
                    return false;
                }
            }

            typeConstraints->FoldDefinitions(universalVar->typeId, specLevel);
            return true;
        }

        void ValidateRecordFields() {
            switch (fieldValidationState) {
                case RecordFieldError::MISSING:
                    std::cout << ERROR_MISSING_RECORD_FIELDS << "\n";
                    exit(1);
                case RecordFieldError::UNEXP:
                    std::cout << ERROR_UNEXPECTED_RECORD_FIELDS << "\n";
                    exit(1);
                default:
                    break;
            }
        }

        void ValidateBooleanPattern() {
            auto currentCtx = Navigate();
            auto matchedType = currentCtx->currentPatternMatchType;

            if (!IsBooleanType(matchedType)) {
                std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                exit(1);
            }
        }

        std::shared_ptr<Type> handleExceptionalCase(std::string exc_class, const std::string& err_msg) {
            auto inferredType = GetCurrentInferredType();
            if (IsTypeUndefined(inferredType)) {
                if (ambiguousTypeAsBottom) {
                    auto bottom = std::make_shared<Bottom>();

                    UpdateLastType(bottom);
                    return bottom;
                }

                if (typeReconstruction) {
                    auto typeVar = std::make_shared<TypeAuto>();

                    UpdateLastType(typeVar);
                    return typeVar;
                }

                std::cout << err_msg << "\n";
                exit(1);
            }

            UpdateLastType(inferredType);
            return inferredType;
        }

        void SubtypingError() {
            if (structuralSubtyping) {
                std::cout << ERROR_UNEXPECTED_SUBTYPE << "\n";
                exit(1);
            }
        }
        void ReconstructionError() {
            if (typeReconstruction) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void UniversalTypesError() {
            if (universalTypes) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }

        bool FunctionsMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto functionType1 = std::dynamic_pointer_cast<Function>(actual);
            auto functionType2 = std::dynamic_pointer_cast<Function>(expected);

            if (IsInvalidFunction(functionType1) || IsInvalidFunction(functionType2)) {
                return false;
            }
            if (functionType1->parameterTypes.size() != functionType2->parameterTypes.size()) {
                return false;
            }
            for (int ar = 0; ar < functionType1->parameterTypes.size(); ar++) {
                auto actualType = functionType1->parameterTypes[ar];
                auto expectedType = functionType2->parameterTypes[ar];
                bool equality = structuralSubtyping ? TypesMatch(expectedType, actualType) : TypesMatch(actualType, expectedType);

                if (!equality) {
                    if (TypesMatch(functionType1->returnType, functionType2->returnType)) {
                        hasParameterError = true;
                    }
                    return false;
                }
            }
            return TypesMatch(functionType1->returnType, functionType2->returnType);
        }

        bool TupleMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto tuple_1 = std::dynamic_pointer_cast<Tuple>(actual);
            auto tuple_2 = std::dynamic_pointer_cast<Tuple>(expected);

            if (tuple_1->size() != tuple_2->size()) {
                hasArityMismatch = true;
                return false;
            }

            for (int i = 0; i < tuple_1->size(); i++) {
                if (!TypesMatch(tuple_1->elementTypes[i], tuple_2->elementTypes[i])) {
                    return false;
                }
            }

            return true;
        }

        bool RecordMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto actualType = std::dynamic_pointer_cast<Record>(actual);
            auto expectedType = std::dynamic_pointer_cast<Record>(expected);

            for (auto& field : expectedType->fieldTypes) {
                if (!actualType->HasField(field.first)) {
                    if (structuralSubtyping) {
                        std::cout << ERROR_MISSING_RECORD_FIELDS << "\n";
                        exit(1);
                    }

                    fieldValidationState = RecordFieldError::MISSING;
                    return false;
                }

                if (!TypesMatch(actualType->access(field.first), field.second)) {
                    if (structuralSubtyping) {
                        SubtypingError();
                    }

                    return false;
                }
            }

            if (actualType->size() > expectedType->size()) {
                if (structuralSubtyping) {
                    return true;
                }

                fieldValidationState = RecordFieldError::UNEXP;
                return false;
            }

            if (!actualType->EachFieldExists()) {
                fieldValidationState = RecordFieldError::MISSING;
                return false;
            }

            if (actualType->size() != expectedType->size()) {
                return false;
            }

            return true;
        }

        bool are_same_variants(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto actualType = std::dynamic_pointer_cast<Variant>(actual);
            auto expectedType = std::dynamic_pointer_cast<Variant>(expected);

            for (auto& variant : actualType->variantTypes) {
                if (!expectedType->HasVariant(variant.first)) {
                    std::cout << ERROR_UNEXPECTED_VARIANT_LABEL << "\n";
                    exit(1);
                }

                if (!TypesMatch(variant.second, expectedType->access(variant.first))) {
                    if (structuralSubtyping) {
                        SubtypingError();
                    }

                    return false;
                }
            }

            if (actualType->size() < expectedType->size()) {
                if (structuralSubtyping) {
                    return true;
                }

                if (actualType->ambiguous) {
                    return true;
                }

                return false;
            }

            if (expectedType->size() != actualType->size()) {
                return false;
            }

            return true;
        }

        bool ReferenceTypesMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto referenceType1 = std::dynamic_pointer_cast<Ref>(actual);
            auto referenceType2 = std::dynamic_pointer_cast<Ref>(expected);

            if (!referenceType1 || !referenceType2) {
                std::cout << "TypeSystem Error: cannot cast two ref types\n";
                exit(1);
            }

            if (IsUnknown(referenceType1->dereferencedType) && !IsUnknown(referenceType2->dereferencedType)) {
                return true;
            }

            if (IsUnknown(referenceType2->dereferencedType) && !IsUnknown(referenceType1->dereferencedType)) {
                return true;
            }

            if (structuralSubtyping) {
                return TypesMatch(referenceType1->dereferencedType, referenceType2->dereferencedType) && TypesMatch(referenceType2->dereferencedType, referenceType1->dereferencedType);
            }

            return TypesMatch(referenceType1->dereferencedType, referenceType2->dereferencedType);
        }

        bool SumTypesMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto sum_1 = std::dynamic_pointer_cast<Sum>(actual);
            auto sum_2 = std::dynamic_pointer_cast<Sum>(expected);

            if (!sum_1 || !sum_2) {
                std::cout << "TypeSystem Error: cannot cast two sum types\n";
                exit(1);
            }

            // Nat+Bool and Bool+Nat
            if (sum_1->left && sum_2->left) {
                if (!TypesMatch(sum_1->left, sum_2->left)) {
                    return false;
                }
            }

            // Nat+Bool and Nat+Nat
            if (sum_1->right && sum_2->right) {
                if (!TypesMatch(sum_1->right, sum_2->right)) {
                    return false;
                }
            }

            if (!sum_1->IsFull() && !sum_2->IsFull()) {
                if (sum_1->IsInl() && sum_2->IsInl()) {
                    return TypesMatch(sum_1->left, sum_2->left);
                }

                if (sum_1->IsInr() && sum_2->IsInr()) {
                    return TypesMatch(sum_1->right, sum_2->right);
                }

                return false;
            }

            InferSumTypeComponents(sum_1, sum_2);
            InferSumTypeComponents(sum_2, sum_1);

            return true;
        }

        bool ListTypesMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto list_1 = std::dynamic_pointer_cast<List>(actual);
            auto list_2 = std::dynamic_pointer_cast<List>(expected);

            if (list_1->AnyType() || list_2->AnyType()) {
                return true;
            }

            return TypesMatch(list_1->currentInnerType, list_2->currentInnerType);
        }

        bool ForallTypesMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto forallType1 = std::dynamic_pointer_cast<Forall>(actual);
            auto forallType2 = std::dynamic_pointer_cast<Forall>(expected);

            if (forallType1->universalVariables.size() != forallType2->universalVariables.size()) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            for (int u = 0; u < forallType1->universalVariables.size(); u++) {
                auto typeParam1 = forallType1->universalVariables[u];
                auto typeParam2 = forallType2->universalVariables[u];

                typeConstraints->define(typeParam1, typeParam2, GetCurrentSpecializationLevel() > 0 ? GetCurrentSpecializationLevel() : 0);

                if (!TypesMatch(typeParam1, typeParam2)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }
            }

            return TypesMatch(forallType1->internal, forallType2->internal);
        }

        bool TypeVariablesMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            typeConstraints->CreateTypeConstraint(actual, expected);

            auto typeVar1 = std::dynamic_pointer_cast<TypeAuto>(actual);
            auto typeVar2 = std::dynamic_pointer_cast<TypeAuto>(expected);

            if (typeVar1) {
                return ProcessTypeEquation(typeVar1);
            }

            if (typeVar2) {
                return ProcessTypeEquation(typeVar2);
            }

            return false;
        }

        bool UniversalTypesMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto typeVar1 = std::dynamic_pointer_cast<TypeAuto>(actual);
            auto typeVar2 = std::dynamic_pointer_cast<TypeAuto>(expected);

            if (typeVar1 && typeVar2) {
                if (typeVar1->typeId == typeVar2->typeId && typeVar1->specLevel == typeVar2->specLevel) {
                    return true;
                }
            }

            if (typeVar1) {
                return ProcessUniversalTypeEquation(typeVar1, expected, typeVar1->specLevel);
            }

            if (typeVar2) {
                return ProcessUniversalTypeEquation(typeVar2, actual, typeVar2->specLevel);
            }

            return false;
        }

        bool TypeBoundsMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            auto actualTop = std::dynamic_pointer_cast<Top>(actual);
            auto expectedTop = std::dynamic_pointer_cast<Top>(expected);

            auto actualBottom = std::dynamic_pointer_cast<Bottom>(actual);
            auto expectedBottom = std::dynamic_pointer_cast<Bottom>(expected);

            if (!actualTop && !expectedTop && !actualBottom && !expectedBottom) {
                return false;
            }

            if (expectedTop) {
                return true;
            }

            if (actualBottom) {
                return true;
            }

            if (expectedBottom || actualTop) {
                if (structuralSubtyping) {
                    std::cout << ERROR_UNEXPECTED_SUBTYPE << "\n";
                } else {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                }
                exit(1);
            }

            return false;
        }

        void IncludeExtensionPattern(std::string& extension_name, const std::string& EXT, bool* indicator) {
            if (extension_name == EXT) {
                *indicator = true;
            }
        }

        std::shared_ptr<Type> ResolveUniversalType(std::shared_ptr<Type> typeVariable) {
            auto univ = std::dynamic_pointer_cast<TypeAuto>(typeVariable);
            if (!univ) {
                return nullptr;
            }

            auto defs = typeConstraints->GetDefinitions(univ->typeId, univ->specLevel);

            if (defs.empty()) {
                return nullptr;
            }

            return defs[0];
        }

    public:
        bool hasMainFunction;

        const int UNKNOWN_SCH = -10;
        const std::string MATCH_ANY = "_";

        bool structuralSubtyping;
        bool ambiguousTypeAsBottom;
        bool typeReconstruction;
        bool universalTypes;

        const std::vector<std::pair<const std::string, bool*>> kExtensionConfiguration = {
            {"#structural-subtyping", &structuralSubtyping},
            {"#ambiguous-type-as-bottom", &ambiguousTypeAsBottom},
            {"#type-reconstruction", &typeReconstruction},
            {"#universal-types", &universalTypes}};

        explicit Env()
            : hasMainFunction(false)
            ,
            structuralSubtyping(false)
            ,
            ambiguousTypeAsBottom(false)
            ,
            typeReconstruction(false)
        {
            symbolBindings = std::make_shared<Env::EnvItem>();
            typeConstraints = std::make_shared<Env::ConstraintsScope>();
            exceptionType = std::make_shared<Unknown>();

            anonymousFunctionId = 0;
            sequenceFunctionId = 0;
            patternMatchId = 0;
            localBindingId = 0;

            hasParameterError = false;
            hasSequenceError = false;
        };

        void LeaveScope() {
            if (contextPath.empty()) {
                std::cout << "TypeSystem Warning: Cannot leave scope - context stack is empty\n";
                return;
            }

            contextPath.pop_back();
        }
        void EnterScope(std::string& scopeName) {
            contextPath.push_back(scopeName);
        }

        void ProcessLanguageExtension(std::string& extensionName) {
            for (auto& ext : kExtensionConfiguration) {
                IncludeExtensionPattern(extensionName, ext.first, ext.second);
            }
        }

        std::shared_ptr<Type> GetVariable(const std::string& name) {
            if (name.size() == 0) {
                return nullptr;
            }

            std::shared_ptr<Type> target = nullptr;

            auto currentCtx = symbolBindings;
            for (auto& entity : contextPath) {
                if (currentCtx->map.find(entity) == currentCtx->map.end()) {
                    return nullptr;
                }

                if (currentCtx->map.find(name) != currentCtx->map.end()) {
                    target = currentCtx->map[name]->item;
                }

                currentCtx = currentCtx->map[entity];
            }

            if (currentCtx == nullptr) {
                return nullptr;
            }

            if (currentCtx->map.find(name) == currentCtx->map.end()) {
                return target;
            }

            return currentCtx->map[name]->item;
        }
        void SetVariable(const std::string& name, std::shared_ptr<Type> item) {
            auto currentCtx = Navigate();
            if (currentCtx == nullptr) {
                return;
            }

            currentCtx->map[name] = std::make_shared<Env::EnvItem>(item);
        }
        void UpdateVariableType(const std::string& name, std::shared_ptr<Type> newType) {
            auto currentCtx = Navigate();
            if (currentCtx == nullptr) {
                return;
            }

            if (currentCtx->map.find(name) == currentCtx->map.end()) {
                std::string currentPosition;
                if (contextPath.size() == 1) {
                    return;
                }

                currentPosition = contextPath.back();
                contextPath.pop_back();

                UpdateVariableType(name, newType);

                contextPath.push_back(currentPosition);
                return;
            }

            currentCtx->map[name]->item = newType;
        }

        std::shared_ptr<Type> GetCurrentType() {
            auto currentCtx = Navigate();
            return currentCtx->lastType;
        }
        void UpdateLastType(std::shared_ptr<Type> lst_t) {
            auto currentCtx = Navigate();
            currentCtx->lastType = lst_t;
        }

        int GetLastInteger() {
            auto currentCtx = Navigate();
            return currentCtx->lastIntegerValue;
        }
        void SetLastInteger(int lst_i) {
            auto currentCtx = Navigate();
            currentCtx->lastIntegerValue = lst_i;
        }

        std::string GetCurrentEntityName() {
            auto currentCtx = Navigate();
            return currentCtx->currentScopeName;
        }
        void SetCurrentEntityName(std::string entityName) {
            auto currentCtx = Navigate();
            currentCtx->currentScopeName = entityName;
        }

        void PushTypeToEvaluationStack(std::shared_ptr<Type> type) {
            assert(type != nullptr && "Cannot push null type");
            typeEvaluationStack.push_back(type);
        }
        void PopTypeFromStack() {
            if (typeEvaluationStack.empty()) {
                throw std::out_of_range("Cannot pop from empty type evaluation stack");
            }
            typeEvaluationStack.pop_back();
        }
        std::vector<std::shared_ptr<Type>> GetTypeSubstack(int typeCheckpoint) {
            return GetSubstack<std::shared_ptr<Type>>(typeCheckpoint, typeEvaluationStack);
        }
        int CreateStackMarker() {
            return typeEvaluationStack.size();
        }

        void PushFieldToBuffer(std::string fieldName) {
            recordFieldsBuffer.push_back(fieldName);
        }
        std::vector<std::string> GetFieldSubstack(int typeCheckpoint) {
            return GetSubstack<std::string>(typeCheckpoint, recordFieldsBuffer);
        }
        int StartFieldCollection() {
            return recordFieldsBuffer.size();
        }

        void PushUniversalVariableName(std::string& universalVarName) {
            universalQuantifiers.push_back(universalVarName);
        }
        std::vector<std::string> GetCurrentUniversalNames() {
            return GetSubstack<std::string>(0, universalQuantifiers);
        }

        int OpenUniversalStack(std::vector<std::shared_ptr<Type>> u_types) {
            int init_size = polyTypeDefinitions.size();
            polyTypeDefinitions.push_back(u_types);

            return init_size;
        }
        std::vector<std::shared_ptr<Type>> ExtractUniversalDefinitions() {
            if (polyTypeDefinitions.empty()) {
                std::cout << "TypeSystem Error: get_cur_univs\n";
                exit(1);
            }

            auto definitions = polyTypeDefinitions.back();
            polyTypeDefinitions.pop_back();

            return definitions;
        }
        void CloseUniversalStack(int expectedStackSize) {
            if (polyTypeDefinitions.size() == expectedStackSize) {
                return;
            }

            if (polyTypeDefinitions.size() > expectedStackSize) {
                std::cout << ERROR_NOT_A_GENERIC_FUNCTION << "\n";
                exit(1);
            }

            if (polyTypeDefinitions.size() < expectedStackSize) {
                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }
        }

        void BeginSpecialization() {
            int specLevel = typeConstraints->typeVariableDefinitions.size();
            typeConstraints->typeVariableDefinitions.push_back({});

            specializationMarkers.push_back(specLevel);
        }
        int GetCurrentSpecializationLevel() {
            if (specializationMarkers.empty()) {
                return -1; // LEVEL_NOT_SPECIFIED
            }

            int currentLevel = specializationMarkers.back();
            if (currentLevel < 0) {
                return -2; // LEVEL_INVALID
            }

            return currentLevel;
        }
        void EndSpecialization() {
            if (specializationMarkers.empty()) {
                std::cout << "TypeSystem Error: EndSpecialization\n";
                exit(1);
            }

            specializationMarkers.pop_back();
        }

        bool GetLValueState() {
            auto currentCtx = Navigate();
            return currentCtx->isLValue;
        }
        void SetLValueState(bool new_lvalue) {
            auto currentCtx = Navigate();
            currentCtx->isLValue = new_lvalue;
        }

        void UpdateReturnType(std::shared_ptr<Type> ret) {
            auto func = ExtractFunctionFromContext();
            func->returnType = ret;
        }
        void upd_arguments(std::shared_ptr<Type> arg) {
            auto func = ExtractFunctionFromContext();
            func->parameterTypes.push_back(arg);
        }

        bool IsUnknown(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Unknown>(entity);
        }
        bool IsTypeVariable(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<TypeAuto>(entity);
        }
        bool IsTopType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Top>(entity);
        }
        bool isBottomType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Bottom>(entity);
        }

        bool IsFunctionType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Function>(entity);
        }
        bool IsForallType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Forall>(entity);
        }
        bool IsTupleType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Tuple>(entity);
        }
        bool IsRecordType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Record>(entity);
        }
        bool IsBooleanType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Bool>(entity);
        }
        bool IsUnitType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Unit>(entity);
        }
        bool IsNatType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Nat>(entity);
        }
        bool IsSumType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Sum>(entity);
        }
        bool IsListType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<List>(entity);
        }
        bool IsRefType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Ref>(entity);
        }
        bool IsVariantType(std::shared_ptr<Type> entity) {
            return IsTypeTemplate<Variant>(entity);
        }

        bool TypesMatch(std::shared_ptr<Type> actual, std::shared_ptr<Type> expected) {
            if (!actual || !expected) {
                return false;
            }

            if (structuralSubtyping || IsVariantType(actual) || ambiguousTypeAsBottom) {
                if (TypeBoundsMatch(actual, expected)) {
                    return true;
                }
            }

            if (typeReconstruction) {
                if (IsTypeVariable(actual) || IsTypeVariable(expected)) {
                    if (!TypeVariablesMatch(actual, expected)) {
                        ReconstructionError();
                    }

                    return true;
                }
            }

            if (universalTypes) {
                if (IsTypeVariable(actual) || IsTypeVariable(expected)) {
                    if (!UniversalTypesMatch(actual, expected)) {
                        UniversalTypesError();
                    }

                    return true;
                }

                if (IsForallType(actual) && IsForallType(expected)) {
                    return ForallTypesMatch(actual, expected);
                }
            }

            if (typeid(*actual) != typeid(*expected)) {
                if (structuralSubtyping) {
                    SubtypingError();
                }

                if (typeReconstruction) {
                    ReconstructionError();
                }

                if (universalTypes) {
                    UniversalTypesError();
                }

                return false;
            }

            if (actual->IsPrimitiveType() && expected->IsPrimitiveType()) {
                return true;
            }

            if (IsFunctionType(actual) && IsFunctionType(expected)) {
                return FunctionsMatch(actual, expected);
            }

            if (IsTupleType(actual) && IsTupleType(expected)) {
                return TupleMatch(actual, expected);
            }

            if (IsRecordType(actual) && IsRecordType(expected)) {
                return RecordMatch(actual, expected);
            }

            if (IsSumType(actual) && IsSumType(expected)) {
                return SumTypesMatch(actual, expected);
            }

            if (IsRefType(actual) && IsRefType(expected)) {
                return ReferenceTypesMatch(actual, expected);
            }

            if (IsListType(actual) && IsListType(expected)) {
                return ListTypesMatch(actual, expected);
            }

            if (IsVariantType(actual) && IsVariantType(expected)) {
                return are_same_variants(actual, expected);
            }

            if (IsUnknown(actual) && IsUnknown(expected)) {
                return true;
            }

            return false;
        }

        bool IsTypeUndefined(std::shared_ptr<Type> undef_type) {
            return IsUnknown(undef_type) || IsEmptyListWithUnknownType(undef_type) || IsNullReference(undef_type);
        }

        void CheckUnexpectedType(std::shared_ptr<Type> maybe, std::shared_ptr<Type> expected) {
            if (auto func = std::dynamic_pointer_cast<Function>(maybe)) {
                if (func->lambdaType) {
                    VerifyTypeAnnotation<Function>(maybe, expected, ERROR_UNEXPECTED_LAMBDA);
                }
            }

            VerifyTypeAnnotation<Tuple>(maybe, expected, ERROR_UNEXPECTED_TUPLE);
            VerifyTypeAnnotation<Sum>(maybe, expected, ERROR_UNEXPECTED_INJECTION);
            VerifyTypeAnnotation<List>(maybe, expected, ERROR_UNEXPECTED_LIST);
            VerifyTypeAnnotation<Record>(maybe, expected, ERROR_UNEXPECTED_RECORD);

            ValidateRecordFields();
        }

        std::shared_ptr<Type> ApplyFunction(std::string functionName, std::shared_ptr<Type> argument) {
            std::vector<std::shared_ptr<TypeCheck::Type>> args;
            args.push_back(argument);

            return ApplyFunction(functionName, args);
        }
        std::shared_ptr<Type> ApplyFunction(std::string functionName, std::vector<std::shared_ptr<Type>> arguments) {
            if (functionName == "") {
                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            auto entity = GetVariable(functionName);
            if (!entity) {
                std::cout << ERROR_UNDEFINED_VARIABLE << "\n";
                exit(1);
            }

            auto func = std::dynamic_pointer_cast<Function>(entity);
            if (!func) {
                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            if (func->parameterTypes.size() != arguments.size()) {
                if (func->isInitLambdaType) {
                    std::cout << ERROR_UNEXPECTED_NUMBER_OF_PARAMETERS_IN_LAMBDA << "\n";
                } else {
                    std::cout << ERROR_INCORRECT_NUMBER_OF_ARGUMENTS << "\n";
                }
                exit(1);
            }

            for (int ar = 0; ar < func->parameterTypes.size(); ar++) {
                if (!TypesMatch(arguments[ar], func->parameterTypes[ar])) {
                    CheckUnexpectedType(arguments[ar], func->parameterTypes[ar]);

                    if (hasParameterError) {
                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_PARAMETER << "\n";
                    } else if (hasArityMismatch) {
                        std::cout << ERROR_UNEXPECTED_TUPLE_LENGTH << "\n";
                    } else {
                        ValidateRecordFields();

                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    }

                    exit(1);
                }
            }

            auto ret = func->returnType;
            if (IsFunctionType(ret)) {
                ClearLambdaFlag(ret);
            }
            if (IsSumType(ret)) {
                auto ret_sum = std::dynamic_pointer_cast<Sum>(ret);
                if (ret_sum) {
                    if (!ret_sum->IsFull()) {
                        std::cout << ERROR_AMBIGUOUS_SUM_TYPE << "\n";
                        exit(1);
                    }
                }
            }
            if (IsListType(ret)) {
                auto ret_lst = std::dynamic_pointer_cast<List>(ret);
                if (ret_lst) {
                    if (IsUnknown(ret_lst->currentInnerType)) {
                        std::cout << ERROR_AMBIGUOUS_LIST_TYPE << "\n";
                        exit(1);
                    }
                }
            }
            if (IsRefType(ret)) {
                if (IsNullReference(ret)) {
                    std::cout << ERROR_AMBIGUOUS_REFERENCE_TYPE << "\n";
                    exit(1);
                }
            }

            UpdateLastType(ret);
            return GetCurrentType();
        }

        std::shared_ptr<Type> AccessMember(std::shared_ptr<Type> entity, int accessor) {
            std::shared_ptr<Tuple> tuple = std::dynamic_pointer_cast<Tuple>(entity);

            if (typeReconstruction && IsTypeVariable(entity)) {
                auto typeVar = std::dynamic_pointer_cast<TypeAuto>(entity);
                auto definitions = typeConstraints->GetDefinitions(typeVar->typeId);

                if (definitions.empty()) {
                    tuple = CreateTypeVariableTuple();
                } else {
                    tuple = std::dynamic_pointer_cast<Tuple>(definitions[0]);
                }
            }

            if (!tuple) {
                std::cout << ERROR_NOT_A_TUPLE << "\n";
                exit(1);
            }

            if (accessor < 1 || accessor > tuple->size()) {
                std::cout << ERROR_TUPLE_INDEX_OUT_OF_BOUNDS << "\n";
                exit(1);
            }

            tuple->elementTypes[accessor - 1]->isAscripted = true;
            return tuple->elementTypes[accessor - 1];
        }
        std::shared_ptr<Type> AccessMember(std::shared_ptr<Type> entity, std::string accessor) {
            auto record = std::dynamic_pointer_cast<Record>(entity);
            if (!IsRecordType(entity) || !record) {
                std::cout << ERROR_NOT_A_RECORD << "\n";
                exit(1);
            }

            if (!record->HasField(accessor)) {
                if (typeReconstruction) {
                    std::cout << ERROR_MISSING_RECORD_FIELDS << "\n";
                    exit(1);
                }

                std::cout << ERROR_UNEXPECTED_FIELD_ACCESS << "\n";
                exit(1);
            }

            record->fieldTypes[accessor]->isAscripted = true;
            return record->fieldTypes[accessor];
        }

        std::shared_ptr<Type> ApplyFixedFunction(std::shared_ptr<Type> fix_) {
            auto fixedFunction = std::dynamic_pointer_cast<Function>(fix_);
            if (!fixedFunction) {
                if (typeReconstruction) {
                    ReconstructionError();
                }

                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            fixedFunction->returnType->isAscripted = true;

            UpdateLastType(fixedFunction->returnType);
            return fixedFunction->returnType;
        }

        void VerifyReturnType(std::shared_ptr<Type> actual_type) {
            auto func = ExtractFunctionFromContext();
            if (!TypesMatch(actual_type, func->returnType)) {
                CheckUnexpectedType(actual_type, func->returnType);

                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void VerifyFunctionApplication(std::string& functionName) {
            if (typeReconstruction) {
                if (auto typeVar = std::dynamic_pointer_cast<TypeAuto>(GetVariable(functionName))) {
                    auto fresh_function = std::make_shared<Function>(
                        std::make_shared<TypeAuto>(),
                        std::make_shared<TypeAuto>());

                    if (!TypesMatch(typeVar, fresh_function)) {
                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                        exit(1);
                    }

                    UpdateVariableType(functionName, fresh_function);

                    return;
                }
            }

            auto func = std::dynamic_pointer_cast<Function>(GetVariable(functionName));
            if (!func) {
                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            auto returns_ = func->returnType;

            auto inferredType = GetCurrentInferredType();
            if (IsUnknown(inferredType)) {
                return;
            }

            if (universalTypes) {
                return;
            }

            if (!TypesMatch(returns_, inferredType)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void VerifyMainFunction(std::shared_ptr<Type> entity) {
            auto main_func = std::dynamic_pointer_cast<Function>(entity);
            if (!IsFunctionType(entity) || !main_func) {
                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            this->hasMainFunction = true;

            if (main_func->parameterTypes.size() != 1) {
                std::cout << ERROR_INCORRECT_ARITY_OF_MAIN << "\n";
                exit(1);
            }
        }
        void VerifyInt(int const_int) {
            if (const_int < 0) {
                std::cout << ERROR_ILLEGAL_NEGATIVE_LITERAL << "\n";
                exit(1);
            }
        }
        void VerifyIfExpression(std::shared_ptr<Type> condition, std::shared_ptr<Type> trueBranchType, std::shared_ptr<Type> elseBranchType) {
            if (typeReconstruction && IsTypeVariable(condition)) {
                auto typeVar = std::dynamic_pointer_cast<TypeAuto>(condition);
                auto definitions = typeConstraints->GetDefinitions(typeVar->typeId);

                if (definitions.empty()) {
                    auto b = std::make_shared<Bool>();
                    if (!TypesMatch(condition, b)) {
                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                        exit(1);
                    }

                    condition = b;
                } else {
                    condition = definitions[0];
                }
            }

            if (!IsBooleanType(condition)) {
                CheckUnexpectedType(condition, std::make_shared<Bool>());

                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            if (IsUnknown(GetCurrentInferredType())) {
                if (!TypesMatch(elseBranchType, trueBranchType)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                return;
            }

            if (!TypesMatch(trueBranchType, GetCurrentInferredType())) {
                CheckUnexpectedType(trueBranchType, GetCurrentInferredType());

                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            if (!TypesMatch(elseBranchType, GetCurrentInferredType())) {
                CheckUnexpectedType(elseBranchType, GetCurrentInferredType());

                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void VerifySumType(std::shared_ptr<Type> sum_type) {
            if (IsUnknown(GetCurrentInferredType())) {
                if (!ambiguousTypeAsBottom && !typeReconstruction) {
                    std::cout << ERROR_AMBIGUOUS_SUM_TYPE << "\n";
                    exit(1);
                } else {
                    auto inl_inr = std::dynamic_pointer_cast<Sum>(sum_type);
                    if (!inl_inr) {
                        std::cout << "TypeSystem Error: cannot cast inl inr (VerifySumType)\n";
                        exit(1);
                    }

                    if (!inl_inr->IsFull()) {
                        ResolveInjectionType(inl_inr);
                    }

                    return;
                }
            }

            if (typeReconstruction) {
                auto inl_inr = std::dynamic_pointer_cast<Sum>(sum_type);
                if (!inl_inr) {
                    std::cout << "TypeSystem Error: cannot cast inl inr (VerifySumType) second\n";
                    exit(1);
                }

                if (!inl_inr->IsFull()) {
                    ResolveInjectionType(inl_inr);
                }
            }

            if (!TypesMatch(sum_type, GetCurrentInferredType())) {
                CheckUnexpectedType(sum_type, GetCurrentInferredType());

                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void VerifyHeadElement(std::shared_ptr<Type> listType) {
            ValidateListOperation(listType, ListFunctionType::HEAD);
        }
        void verify_tail(std::shared_ptr<Type> listType) {
            ValidateListOperation(listType, ListFunctionType::TAIL);
        }
        void VerifyEmptyList(std::shared_ptr<Type> listType) {
            ValidateListOperation(listType, ListFunctionType::ISEMPTY);
        }
        void VerifyRecursiveType(std::shared_ptr<Type> n, std::shared_ptr<Type> z, std::shared_ptr<Type> s) {
            auto rec_counter = std::dynamic_pointer_cast<Nat>(n);
            auto rec_init = z;
            auto rec = std::dynamic_pointer_cast<Function>(s);

            if (typeReconstruction) {
                if (IsTypeVariable(n)) {
                    rec_counter = std::make_shared<Nat>();
                    if (!TypesMatch(n, rec_counter)) {
                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                        exit(1);
                    }
                }

                if (IsTypeVariable(s)) {
                    rec = CreateFunctionWithTypeVariables();
                    if (!TypesMatch(s, rec)) {
                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                        exit(1);
                    }
                }
            }

            if (!rec_counter) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            if (!rec) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
            std::string rec_name = generateAnonymousFunctionTag();
            SetVariable(rec_name, rec);
            auto ret_lambda = ApplyFunction(rec_name, rec_counter);

            if (!IsFunctionType(ret_lambda)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            SetVariable(rec_name, ret_lambda);
            auto ret_type = ApplyFunction(rec_name, rec_init);

            if (!TypesMatch(ret_type, rec_init)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void VerifyTypeAscription(std::shared_ptr<Type> expr_type, std::shared_ptr<Type> as_type) {
            expr_type->isAscripted = true;
            as_type->isAscripted = true;

            if (!TypesMatch(expr_type, as_type)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            if (IsSumType(expr_type) && IsSumType(as_type)) {
                InferSumTypeComponents(expr_type, as_type);
            }

            if (!IsUnknown(GetCurrentInferredType()) && !TypesMatch(as_type, GetCurrentInferredType())) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void InferSumTypeComponents(std::shared_ptr<Type> targetSum, std::shared_ptr<Type> sourceSum) {
            auto target = std::dynamic_pointer_cast<Sum>(targetSum);
            auto source = std::dynamic_pointer_cast<Sum>(sourceSum);
            if (!source || !target) {
                return;
            }

            if (target->IsFull()) {
                return;
            }

            if (!target->IsInl()) {
                target->left = source->left;
                return;
            }
            if (!target->IsInr()) {
                target->right = source->right;
                return;
            }
        }
        void ValidatePatternMatching(std::vector<std::shared_ptr<Type>> types) {
            if (types.empty()) {
                std::cout << ERROR_ILLEGAL_EMPTY_MATCHING << "\n";
                exit(1);
            }

            auto inferredType = GetCurrentInferredType();
            for (auto& match_type : types) {
                if (!TypesMatch(match_type, inferredType)) {
                    std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                    exit(1);
                }
            }

            UpdateLastType(inferredType);
        }
        void VerifyListInitialization(std::vector<std::shared_ptr<Type>> init_items) {
            auto inferredType = GetCurrentInferredType();

            if (init_items.empty()) {
                if (IsUnknown(inferredType) || IsEmptyListWithUnknownType(inferredType)) {
                    if (ambiguousTypeAsBottom || typeReconstruction) {
                        std::shared_ptr<Type> replace;

                        if (ambiguousTypeAsBottom) {
                            replace = std::make_shared<Bottom>();
                        } else if (typeReconstruction) {
                            replace = std::make_shared<TypeAuto>();
                        }

                        UpdateLastType(replace);
                        return;
                    } else {
                        std::cout << ERROR_AMBIGUOUS_LIST_TYPE << "\n";
                        exit(1);
                    }
                }

                UpdateLastType(inferredType);
                return;
            }

            if (IsUnknown(inferredType) || IsEmptyListWithUnknownType(inferredType)) {
                PopInferenceContext();
                PushInferenceContext(init_items[0]);
                inferredType = GetCurrentInferredType();
            }

            for (auto& list_entity : init_items) {
                if (!TypesMatch(list_entity, inferredType)) {
                    CheckUnexpectedType(list_entity, inferredType);

                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }
            }

            UpdateLastType(inferredType);
        }
        void VerifyConstructor(std::shared_ptr<Type> cons_item_, std::shared_ptr<Type> cons_list_) {
            auto inferredType = GetCurrentInferredType();

            auto infer_list = std::dynamic_pointer_cast<List>(inferredType);
            auto cons_list = std::dynamic_pointer_cast<List>(cons_list_);
            if (!cons_list) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            if (IsUnknown(cons_list->currentInnerType) && IsUnknown(cons_item_)) {
                if (IsUnknown(inferredType) || !infer_list) {
                    std::cout << ERROR_AMBIGUOUS_LIST_TYPE << "\n";
                    exit(1);
                }

                cons_list = infer_list;
                cons_item_ = infer_list->currentInnerType;
            }

            if (IsUnknown(cons_list->currentInnerType)) {
                cons_list->currentInnerType = cons_item_;

                UpdateLastType(cons_list);
            }
            if (IsUnknown(cons_item_)) {
                cons_item_ = cons_list->currentInnerType;
            }

            if (!TypesMatch(cons_item_, cons_list->currentInnerType)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            if (IsUnknown(inferredType)) {
                UpdateLastType(cons_list);
                return;
            }
            if (!TypesMatch(cons_list_, inferredType)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            UpdateLastType(cons_list);
        }
        void VerifyRecordType(std::shared_ptr<Type> record_) {
            if (IsUnknown(GetCurrentInferredType())) {
                return;
            }

            auto inferred = std::dynamic_pointer_cast<Record>(GetCurrentInferredType());
            auto recordInstance = std::dynamic_pointer_cast<Record>(record_);
            if (!inferred || !recordInstance) {
                std::cout << ERROR_UNEXPECTED_RECORD << "\n";
                exit(1);
            }

            if (!TypesMatch(recordInstance, inferred)) {
                switch (fieldValidationState) {
                    case RecordFieldError::MISSING:
                        std::cout << ERROR_MISSING_RECORD_FIELDS << "\n";
                        exit(1);
                    case RecordFieldError::UNEXP:
                        std::cout << ERROR_UNEXPECTED_RECORD_FIELDS << "\n";
                        exit(1);
                    default:
                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                        exit(1);
                }
            }
        }
        void ValidateFixpoint(std::shared_ptr<Type> fix_) {
            auto fixedFunction = std::dynamic_pointer_cast<Function>(fix_);
            if (!fixedFunction) {
                if (typeReconstruction) {
                    ReconstructionError();
                }

                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            if (fixedFunction->parameterTypes.size() != 1) {
                std::cout << ERROR_INCORRECT_NUMBER_OF_ARGUMENTS << "\n";
                exit(1);
            }

            if (!TypesMatch(fixedFunction->parameterTypes[0], fixedFunction->returnType)) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void VerifyThrowExpression(std::shared_ptr<Type> throw_) {

            if (!TypesMatch(throw_, exceptionType)) {
                CheckUnexpectedType(throw_, exceptionType);

                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }
        void VerifyTryExpression(std::shared_ptr<Type> replaced) {

            if (!TypesMatch(replaced, GetCurrentInferredType())) {
                CheckUnexpectedType(replaced, GetCurrentInferredType());

                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }
        }

        void PushApplication(std::string appl) {
            callTrace.push_back(appl);
        }
        std::string PopApplication() {
            if (callTrace.size() == 0) {
                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            auto lastApplication = callTrace.back();
            callTrace.pop_back();

            return lastApplication;
        }

        void VerifyExhaustiveness() {
            if (!IsSumType(GetCurrentInferredType()) && GetCurrentEntityName() != "" && !IsVariantType(GetCurrentInferredType())) {
                MarkFirstPatternMatchRequirement();
                MarkSecondPatternMatchRequirement();
            }
        }

        void OpenMatchCase() {
            patternMatchFlags.push_back(std::pair<bool, bool>(false, false));
        }
        void close_match() {
            if (patternMatchFlags.size() == 0) {
                std::cout << "TypeSystem Error: cannot pop from empty match stack\n";
                exit(1);
            }

            auto lst_pair = patternMatchFlags.back();
            patternMatchFlags.pop_back();

            if (!lst_pair.first || !lst_pair.second) {
                std::cout << ERROR_NONEXHAUSTIVE_MATCH_PATTERNS << "\n";
                exit(1);
            }
        }
        void RemoveMatchCase() {
            if (patternMatchFlags.size() == 0) {
                std::cout << "TypeSystem Error: cannot pop from empty match stack (RemoveMatchCase)\n";
                exit(1);
            }

            patternMatchFlags.pop_back();
        }
        void InitializePatternMatch(std::shared_ptr<Type> expr) {
            if (IsSumType(expr)) {
                std::shared_ptr<Sum> sum_type = std::dynamic_pointer_cast<Sum>(expr);
                if (!sum_type) {
                    std::cout << "TypeSystem Error: InitializePatternMatch\n";
                    exit(1);
                }

                if (!sum_type->IsFull()) {
                    std::cout << ERROR_AMBIGUOUS_SUM_TYPE << "\n";
                    exit(1);
                }
            }

            if (IsVariantType(expr)) {
                std::shared_ptr<Variant> variant_type = std::dynamic_pointer_cast<Variant>(expr);
                if (variant_type->ambiguous) {
                    std::cout << ERROR_AMBIGUOUS_VARIANT_TYPE << "\n";
                    exit(1);
                }

                variant_type->ClearMarks();
            }

            auto currentCtx = Navigate();
            currentCtx->patternMatchInitialType = expr;
            currentCtx->currentPatternMatchType = expr;
        }
        void ResetPatternMatching() {
            auto currentCtx = Navigate();
            currentCtx->currentPatternMatchType = currentCtx->patternMatchInitialType;
        }
        void MatchInlPattern() {
            MarkFirstPatternMatchRequirement();

            ProcessInjectionMatch(
                [](std::shared_ptr<Sum> sum_type) { return sum_type->IsInl(); },
                [](std::shared_ptr<Sum> sum_type) { return sum_type->left; },
                "inl");
        }
        void MatchInrPattern() {
            MarkSecondPatternMatchRequirement();

            ProcessInjectionMatch(
                [](std::shared_ptr<Sum> sum_type) { return sum_type->IsInr(); },
                [](std::shared_ptr<Sum> sum_type) { return sum_type->right; },
                "inr");
        }
        void MatchEmptyListPattern() {
            MarkFirstPatternMatchRequirement();
        }
        void MatchConsPattern() {
            MarkSecondPatternMatchRequirement();
        }
        void MatchTruePattern() {
            MarkFirstPatternMatchRequirement();
            ValidateBooleanPattern();
        }
        void MatchFalsePattern() {
            MarkSecondPatternMatchRequirement();
            ValidateBooleanPattern();
        }
        void MatchAnyPattern() {
            MarkFirstPatternMatchRequirement();
            MarkSecondPatternMatchRequirement();
        }
        void MatchUnitPattern() {
            MarkFirstPatternMatchRequirement();
            MarkSecondPatternMatchRequirement();

            auto currentCtx = Navigate();
            auto matchedType = currentCtx->currentPatternMatchType;

            if (!IsUnitType(matchedType)) {
                std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                exit(1);
            }
        }
        void MatchIntPattern() {
            auto currentCtx = Navigate();
            auto matchedType = currentCtx->currentPatternMatchType;

            if (!IsNatType(matchedType)) {
                std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                exit(1);
            }
        }
        void MatchSuccPattern() {
            auto currentCtx = Navigate();
            auto matchedType = currentCtx->currentPatternMatchType;

            if (!IsNatType(matchedType)) {
                std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                exit(1);
            }
        }
        void MatchVariantPattern(std::string& label) {
            auto currentCtx = Navigate();
            auto matchedType = std::dynamic_pointer_cast<Variant>(currentCtx->currentPatternMatchType);

            if (!matchedType) {
                std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                exit(1);
            }

            if (!matchedType->HasVariant(label)) {
                std::cout << ERROR_UNEXPECTED_PATTERN_FOR_TYPE << "\n";
                exit(1);
            }

            matchedType->match_label(label);
            if (matchedType->EachFieldExists()) {
                MarkFirstPatternMatchRequirement();
                MarkSecondPatternMatchRequirement();
            }

            auto accessed = matchedType->access(label);
            if (!accessed) {
                std::cout << "TypeSystem Error: cannot match variant\n";
                exit(1);
            }
            currentCtx->currentPatternMatchType = accessed;

            if (IsFunctionType(currentCtx->currentPatternMatchType)) {
                ClearLambdaFlag(currentCtx->currentPatternMatchType);
            }
        }

        std::shared_ptr<Type> GetMatchedVariable() {
            auto currentCtx = Navigate();
            return currentCtx->currentPatternMatchType;
        }

        void MarkAsLambda(std::shared_ptr<Type> entity) {
            if (IsFunctionType(entity)) {
                auto func = std::dynamic_pointer_cast<Function>(entity);
                if (!func) {
                    std::cout << "TypeSystem Error: item is not a function (MarkAsLambda call)\n";
                    exit(1);
                }

                func->lambdaType = true;
                func->isInitLambdaType = true;
            }
        }

        void PushInferenceContext(std::shared_ptr<Type> inferredType) {
            typeInferenceBuffer.push_back(inferredType);
        }
        std::shared_ptr<Type> GetCurrentInferredType() {
            if (typeInferenceBuffer.empty()) {
                std::cout << "TypeSystem Error: infer stack is empty, cannot extract\n";
                exit(1);
            }

            return typeInferenceBuffer.back();
        }
        void PopInferenceContext() {
            if (typeInferenceBuffer.empty()) {
                std::cout << "TypeSystem Error: infer stack is empty, cannot close\n";
                exit(1);
            }

            typeInferenceBuffer.pop_back();
        }
        std::shared_ptr<Type> InferListElementType() {
            auto inferredType = GetCurrentInferredType();

            if (IsUnknown(inferredType)) {
                UpdateLastType(inferredType);
                return inferredType;
            }

            if (structuralSubtyping && IsTopType(inferredType)) {
                UpdateLastType(inferredType);
                return inferredType;
            }

            if (typeReconstruction && IsTypeVariable(inferredType)) {
                auto inner_fresh = std::make_shared<TypeAuto>();
                auto fresh_list = std::make_shared<List>(inner_fresh);

                if (!TypesMatch(fresh_list, inferredType)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                UpdateLastType(inner_fresh);
                return inner_fresh;
            }

            auto cur_list = std::dynamic_pointer_cast<List>(inferredType);
            if (universalTypes && !cur_list) {
                cur_list = std::dynamic_pointer_cast<List>(ResolveUniversalType(inferredType));
            }

            if (!cur_list) {
                if (typeReconstruction) {
                    ReconstructionError();
                }

                std::cout << ERROR_UNEXPECTED_LIST << "\n";
                exit(1);
            }

            UpdateLastType(cur_list->currentInnerType);
            return cur_list->currentInnerType;
        }
        std::shared_ptr<Type> InferListContainer() {
            auto inferredType = GetCurrentInferredType();
            auto cur_list = std::make_shared<List>(inferredType);

            UpdateLastType(cur_list);
            return cur_list;
        }
        std::shared_ptr<Type> InferListStructure() {
            auto inferredType = GetCurrentInferredType();

            if (IsUnknown(inferredType)) {
                auto AnyType_list = std::make_shared<List>(inferredType);
                UpdateLastType(AnyType_list);
                return AnyType_list;
            }

            auto cur_list = std::dynamic_pointer_cast<List>(inferredType);
            if (!IsListType(inferredType) || !cur_list) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            UpdateLastType(cur_list);
            return cur_list;
        }
        std::shared_ptr<Type> InferFromConstructor(std::shared_ptr<Type> cons_item) {
            if (IsUnknown(GetCurrentInferredType())) {
                PopInferenceContext();
                auto new_list = std::make_shared<List>(cons_item);

                PushInferenceContext(new_list);
                return new_list;

            } else {
                return GetCurrentInferredType();
            }
        }
        std::shared_ptr<Type> InferEmptyList() {
            auto inferredType = GetCurrentInferredType();
            auto any_list = std::make_shared<List>(true);

            UpdateLastType(any_list);
            return any_list;
        }
        std::shared_ptr<Type> InferLeftInjection() {
            return InferInjectionType([](std::shared_ptr<Sum> sum_type) { return sum_type->left; });
        }
        std::shared_ptr<Type> InferRightInjection() {
            return InferInjectionType([](std::shared_ptr<Sum> sum_type) { return sum_type->right; });
        }
        std::vector<std::shared_ptr<Type>> InferFunctionArguments(std::string functionName) {
            auto func = std::dynamic_pointer_cast<Function>(GetVariable(functionName));
            if (!func) {
                std::cout << ERROR_NOT_A_FUNCTION << "\n";
                exit(1);
            }

            ScheduleTypeInferences(func->parameterTypes.size());
            return func->parameterTypes;
        }
        std::shared_ptr<Type> InferLambdaReturnType(std::string lambda_name) {
            if (IsTypeUndefined(GetCurrentInferredType()) || typeReconstruction && GetCurrentInferredType()->ContainsTypeVar(AUTO_ANY)) {
                auto lam = std::dynamic_pointer_cast<Function>(GetVariable(lambda_name));
                if (!lam) {
                    std::cout << ERROR_NOT_A_FUNCTION << "\n";
                    exit(1);
                }

                return lam->returnType;
            } else {
                auto lam = std::dynamic_pointer_cast<Function>(GetCurrentInferredType());
                if (universalTypes && !lam) {
                    lam = std::dynamic_pointer_cast<Function>(ResolveUniversalType(GetCurrentInferredType()));
                }

                if (!lam) {
                    if (typeReconstruction) {
                        ReconstructionError();
                    }

                    std::cout << ERROR_UNEXPECTED_LAMBDA << "\n";
                    exit(1);
                }

                return lam->returnType;
            }
        }
        std::shared_ptr<Type> InferInsideRecord() {
            auto inferredType = GetCurrentInferredType();

            auto identityFunction = std::make_shared<Function>(inferredType, inferredType);
            auto recursiveFunction = std::make_shared<Function>(std::make_shared<Nat>(), identityFunction);

            UpdateLastType(recursiveFunction);
            return recursiveFunction;
        }

        std::vector<std::shared_ptr<Type>> InferTupleComponents() {
            if (IsUnknown(GetCurrentInferredType())) {
                ScheduleTypeInferences(-10);
                return std::vector<std::shared_ptr<Type>>();
            }

            if (typeReconstruction && IsTypeVariable(GetCurrentInferredType())) {
                auto fresh_tuple = CreateTypeVariableTuple();

                ScheduleTypeInferences(fresh_tuple->elementTypes.size());
                return fresh_tuple->elementTypes;
            }

            auto tupleType = std::dynamic_pointer_cast<Tuple>(GetCurrentInferredType());
            if (!tupleType) {
                std::cout << ERROR_UNEXPECTED_TUPLE << "\n";
                exit(1);
            }

            ScheduleTypeInferences(tupleType->elementTypes.size());
            return tupleType->elementTypes;
        }
        std::shared_ptr<Type> InferRecordType() {
            if (IsUnknown(GetCurrentInferredType())) {
                return std::make_shared<Record>();
            }

            auto inferredRecordType = std::dynamic_pointer_cast<Record>(GetCurrentInferredType());
            if (!inferredRecordType) {
                std::cout << ERROR_UNEXPECTED_RECORD << "\n";
                exit(1);
            }

            std::shared_ptr<Record> recordInstance = std::make_shared<Record>(inferredRecordType);
            return recordInstance;
        }
        std::shared_ptr<Type> InferFieldType(std::string field) {
            if (IsUnknown(GetCurrentInferredType())) {
                return std::make_shared<Unknown>();
            }

            auto inferredRecordType = std::dynamic_pointer_cast<Record>(GetCurrentInferredType());
            if (!inferredRecordType) {
                std::cout << ERROR_UNEXPECTED_RECORD << "\n";
                exit(1);
            }

            if (!inferredRecordType->HasField(field)) {
                return std::make_shared<Unknown>();
            }

            return inferredRecordType->access(field);
        }
        std::shared_ptr<Type> InferTupleElement(int accessor) {
            auto inferredType = GetCurrentInferredType();

            if (IsUnknown(inferredType)) {
                UpdateLastType(inferredType);
                return inferredType;
            }

            auto tupleType = std::dynamic_pointer_cast<Tuple>(inferredType);
            if (!tupleType) {
                std::cout << ERROR_UNEXPECTED_TUPLE << "\n";
                exit(1);
            }

            auto accessed = tupleType->elementTypes[accessor - 1];

            UpdateLastType(accessed);
            return accessed;
        }
        std::shared_ptr<Type> InferDereferencedType() {
            auto inferredType = GetCurrentInferredType();
            auto any_ref = std::make_shared<Ref>(inferredType);

            UpdateLastType(any_ref);
            return any_ref;
        }
        std::shared_ptr<Type> InferReferenceType() {
            auto inferredType = GetCurrentInferredType();
            if (IsUnknown(inferredType)) {
                UpdateLastType(inferredType);
                return inferredType;
            }

            auto referenceType = std::dynamic_pointer_cast<Ref>(inferredType);
            if (typeReconstruction && IsTypeVariable(inferredType)) {
                auto typeVar = std::dynamic_pointer_cast<TypeAuto>(inferredType);
                auto typeVarRef = CreateReferenceWithTypeVariable();

                if (!TypesMatch(typeVar, typeVarRef)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                referenceType = typeVarRef;
            }

            if (!referenceType) {
                std::cout << ERROR_NOT_A_REFERENCE << "\n";
                exit(1);
            }

            UpdateLastType(referenceType->dereferencedType);
            return referenceType->dereferencedType;
        }
        std::shared_ptr<Type> InferSequenceType() {
            auto exp = std::make_shared<Unit>();

            UpdateLastType(exp);
            return exp;
        }
        std::shared_ptr<Type> InferMemoryReferenceType() {
            auto inferredType = GetCurrentInferredType();
            if (typeReconstruction && IsTypeVariable(inferredType)) {
                auto typeVar = std::dynamic_pointer_cast<TypeAuto>(inferredType);
                auto typeVarRef = CreateReferenceWithTypeVariable();

                if (!TypesMatch(typeVar, typeVarRef)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                UpdateLastType(typeVarRef);
                return typeVarRef;
            }

            if (IsUnknown(inferredType)) {
                std::cout << ERROR_AMBIGUOUS_REFERENCE_TYPE << "\n";
                exit(1);
            }

            auto referenceType = std::dynamic_pointer_cast<Ref>(inferredType);
            if (!referenceType) {
                std::cout << ERROR_UNEXPECTED_MEMORY_ADDRESS << "\n";
                exit(1);
            }

            UpdateLastType(referenceType);
            return referenceType;
        }
        std::shared_ptr<Type> InferFixedPoint() {
            auto inferredType = GetCurrentInferredType();

            std::shared_ptr<Function> fixedFunction = std::make_shared<Function>(inferredType, inferredType);

            UpdateLastType(fixedFunction);
            return fixedFunction;
        }
        std::shared_ptr<Type> InferExceptionType() {
            if (IsUnknown(exceptionType)) {
                std::cout << ERROR_EXCEPTION_TYPE_NOT_DECLARED << "\n";
                exit(1);
            }

            UpdateLastType(exceptionType);
            return exceptionType;
        }
        std::shared_ptr<Type> InferVariantType(std::string& label_) {
            if (IsUnknown(GetCurrentInferredType())) {
                if (!structuralSubtyping) {
                    std::cout << ERROR_AMBIGUOUS_VARIANT_TYPE << "\n";
                    exit(1);
                } else {
                    return GetCurrentInferredType();
                }
            }

            if (IsTopType(GetCurrentInferredType())) {
                return std::make_shared<Unknown>();
            }

            auto variant = std::dynamic_pointer_cast<Variant>(GetCurrentInferredType());
            if (!variant) {
                std::cout << ERROR_UNEXPECTED_VARIANT << "\n";
                exit(1);
            }

            if (!variant->HasVariant(label_)) {
                std::cout << ERROR_UNEXPECTED_VARIANT_LABEL << "\n";
                exit(1);
            }

            auto accessed = variant->access(label_);

            UpdateLastType(accessed);
            return accessed;
        }
        std::shared_ptr<Type> InferWIthForall() {
            auto inferredType = GetCurrentInferredType();
            if (IsUnknown(inferredType)) {
                return std::make_shared<Forall>(inferredType);
            }

            auto forall = std::dynamic_pointer_cast<Forall>(inferredType);
            if (!forall) {
                forall = std::dynamic_pointer_cast<Forall>(ResolveUniversalType(inferredType));
            }

            if (!forall) {
                std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                exit(1);
            }

            auto internal = forall->internal;

            UpdateLastType(internal);
            return internal;
        }

        void ScheduleTypeInferences(int mult_infers) {
            multiInferenceMarkers.push_back(mult_infers);
        }
        int GetScheduledInferenceCount() {
            return multiInferenceMarkers.back();
        }
        bool HasScheduledInferences() {
            return multiInferenceMarkers.back() > 0;
        }
        void CompleteScheduledInference() {
            auto sch = multiInferenceMarkers.back();
            if (sch--> 0) {
                multiInferenceMarkers.pop_back();
                multiInferenceMarkers.push_back(sch);
            }
        }
        void ClearInferenceSchedule() {
            multiInferenceMarkers.pop_back();
        }
        void MarkScheduleInvalid() {
            auto sch = multiInferenceMarkers.back();
            if (!sch) {
                multiInferenceMarkers.pop_back();
                multiInferenceMarkers.push_back(UNKNOWN_SCH);
            }
        }
        bool IsInferenceScheduleEmpty() {
            return multiInferenceMarkers.back() == 0;
        }

        void DefineRecordField(std::string bindingName, std::shared_ptr<Type> field_type) {
            auto inferred = std::dynamic_pointer_cast<Record>(GetCurrentInferredType());
            if (!inferred) {
                std::cout << ERROR_UNEXPECTED_RECORD << "\n";
                exit(1);
            }

            if (!inferred->HasField(bindingName)) {
                inferred->AddField(bindingName, field_type);
            } else {
                if (!TypesMatch(field_type, inferred->access(bindingName))) {
                    if (!structuralSubtyping) {
                        CheckUnexpectedType(field_type, inferred->access(bindingName));

                        std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                        exit(1);
                    } else {
                        inferred->fieldTypes[bindingName] = field_type;
                    }
                }

                inferred->field_exst(bindingName);
            }
        }

        bool CanCreateLambdaType(std::shared_ptr<Type> type_to_check) {
            if (typeReconstruction) {
                if (auto typeVar = std::dynamic_pointer_cast<TypeAuto>(type_to_check)) {
                    auto fresh_lambda = CreateFunctionWithTypeVariables();

                    if (TypesMatch(typeVar, fresh_lambda)) {
                        UpdateLastType(fresh_lambda);
                        return true;
                    } else {
                        return false;
                    }
                }
            }

            return false;
        }

        std::shared_ptr<TypeAuto> CreateUniversalType(std::string name) {
            std::shared_ptr<TypeAuto> universalType = std::make_shared<TypeAuto>();
            SetVariable(name, universalType);

            return universalType;
        }

        void IncorrectTypeOfMain() {
            std::cout << ERROR_INCORRECT_TYPE_OF_MAIN << "\n";
            exit(1);
        }

        std::shared_ptr<Unit> GetAssignmentResultType() {
            return std::make_shared<Unit>();
        }

        std::shared_ptr<Type> DereferenceType(std::shared_ptr<Type> ref_) {
            auto dereferencedType = std::dynamic_pointer_cast<Ref>(ref_);
            if (typeReconstruction && IsTypeVariable(ref_)) {
                auto typeVar = std::dynamic_pointer_cast<TypeAuto>(ref_);
                auto typeVarRef = CreateReferenceWithTypeVariable();

                if (!TypesMatch(typeVar, typeVarRef)) {
                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                dereferencedType = typeVarRef;
            }

            if (!dereferencedType) {
                std::cout << ERROR_NOT_A_REFERENCE << "\n";
                exit(1);
            }

            if (IsUnknown(dereferencedType->dereferencedType)) {
                std::cout << ERROR_AMBIGUOUS_REFERENCE_TYPE << "\n";
                exit(1);
            }

            UpdateLastType(dereferencedType->dereferencedType);
            return dereferencedType->dereferencedType;
        }
        std::shared_ptr<Type> CreateReferenceType(std::shared_ptr<Type> item_) {
            auto newReference = std::make_shared<Ref>(item_);

            UpdateLastType(newReference);
            return newReference;
        }

        void SetExceptionType(std::shared_ptr<Type> type_) {
            exceptionType = type_;
        }
        std::shared_ptr<Type> GetExceptionType() {
            if (IsUnknown(exceptionType)) {
                std::cout << ERROR_EXCEPTION_TYPE_NOT_DECLARED << "\n";
                exit(1);
            }

            return exceptionType;
        }

        std::shared_ptr<Type> CreateVariant(std::string& variant_label, std::shared_ptr<Type> variant_type) {
            if (IsUnknown(GetCurrentInferredType()) || IsTopType(GetCurrentInferredType())) {
                auto variant = std::make_shared<TypeCheck::Variant>(variant_label, variant_type);

                UpdateLastType(variant);
                return variant;
            } else {
                auto variant = std::dynamic_pointer_cast<Variant>(GetCurrentInferredType());
                if (!variant) {
                    std::cout << ERROR_UNEXPECTED_VARIANT << "\n";
                    exit(1);
                }

                if (!variant->HasVariant(variant_label)) {
                    std::cout << ERROR_UNEXPECTED_VARIANT_LABEL << "\n";
                    exit(1);
                }

                if (!TypesMatch(variant_type, variant->access(variant_label))) {
                    CheckUnexpectedType(variant_type, variant->access(variant_label));

                    std::cout << ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
                    exit(1);
                }

                UpdateLastType(variant);
                return variant;
            }
        }

        void ApplyUniversalTypeDefinitions(std::shared_ptr<Type> functionType) {
            if (!universalTypes) {
                return;
            }

            auto forall = std::dynamic_pointer_cast<Forall>(functionType->Clone());
            if (!forall) {
                std::cout << ERROR_NOT_A_GENERIC_FUNCTION << "\n";
                exit(1);
            }

            auto typeDefinitions = ExtractUniversalDefinitions();
            if (forall->universalVariables.size() != typeDefinitions.size()) {
                std::cout << ERROR_INCORRECT_NUMBER_OF_TYPE_ARGUMENTS << "\n";
                exit(1);
            }

            currentSpecLevel = GetCurrentSpecializationLevel();
            for (int u = 0; u < typeDefinitions.size(); u++) {
                auto typeParam = forall->universalVariables[u];
                auto typeDef = typeDefinitions[u];

                if (GetCurrentSpecializationLevel() < 0) {
                    std::cout << ERROR_NOT_A_FUNCTION << "\n";
                    exit(1);
                }

                typeConstraints->define(typeParam, typeDef, GetCurrentSpecializationLevel());
                typeParam->specLevel = GetCurrentSpecializationLevel();
                forall->ContainsTypeVar(typeParam->typeId);
            }
            currentSpecLevel = SPEC_LEVEL_DISABLED;

            if (GetCurrentEntityName() != "") {
                SetVariable(GetCurrentEntityName(), forall->internal);
            }

            UpdateLastType(forall->internal);
        }

        std::shared_ptr<Type> ResolveUniversalType(std::string& var_id) {
            auto entity = GetVariable(var_id);
            if (!entity) {
                std::cout << ERROR_UNDEFINED_TYPE_VARIABLE << "\n";
                exit(1);
            }

            UpdateLastType(entity);
            return entity;
        }

        void AddUniversalQuantifiersToLambda(std::shared_ptr<Type> func_) {
            if (universalTypes) {
                auto genericFunction = std::dynamic_pointer_cast<Forall>(func_);
                if (!genericFunction) {
                    std::cerr << "TypeSystem Error: Expected generic function type but got: ";
                    std::cerr << "\n";
                    exit(1);
                }

                for (auto& universalVarName : GetCurrentUniversalNames()) {
                    genericFunction->universalVariables.push_back(CreateUniversalType(universalVarName));
                }
            }
        }

        std::shared_ptr<Type> handleThrowableType() {
            return handleExceptionalCase("thrown", ERROR_AMBIGUOUS_THROW_TYPE);
        }
        std::shared_ptr<Type> handlePanicType() {
            return handleExceptionalCase("panic", ERROR_AMBIGUOUS_PANIC_TYPE);
        }

        std::string generateLetBindingIdentifier() {
            return ".let_" + std::to_string(localBindingId++);
        }
        std::string generateAnonymousFunctionTag() {
            return ".lambda_" + std::to_string(anonymousFunctionId++);
        }
        std::string generatePatternMatchingLabel() {
            return ".match_" + std::to_string(patternMatchId++);
        }
        std::string generateTypeQuantifierTag() {
            return ".forall_" + std::to_string(universalQuantifierId++);
        }
    };

} // namespace TypeCheck
