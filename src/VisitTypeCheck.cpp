#include "VisitTypeCheck.h"
#include <iostream>
#include <memory>
#include <vector>
#include <string>

namespace Stella {
    void VisitTypeCheck::visitProgram(Program* t) {
    } // abstract class
    void VisitTypeCheck::visitLanguageDecl(LanguageDecl* t) {
    } // abstract class
    void VisitTypeCheck::visitExtension(Extension* t) {
    } // abstract class
    void VisitTypeCheck::visitDecl(Decl* t) {
    } // abstract class
    void VisitTypeCheck::visitLocalDecl(LocalDecl* t) {
    } // abstract class
    void VisitTypeCheck::visitAnnotation(Annotation* t) {
    } // abstract class
    void VisitTypeCheck::visitParamDecl(ParamDecl* t) {
    } // abstract class
    void VisitTypeCheck::visitReturnType(ReturnType* t) {
    } // abstract class
    void VisitTypeCheck::visitThrowType(ThrowType* t) {
    } // abstract class
    void VisitTypeCheck::visitType(Type* t) {
    } // abstract class
    void VisitTypeCheck::visitMatchCase(MatchCase* t) {
    } // abstract class
    void VisitTypeCheck::visitOptionalTyping(OptionalTyping* t) {
    } // abstract class
    void VisitTypeCheck::visitPatternData(PatternData* t) {
    } // abstract class
    void VisitTypeCheck::visitExprData(ExprData* t) {
    } // abstract class
    void VisitTypeCheck::visitPattern(Pattern* t) {
    } // abstract class
    void VisitTypeCheck::visitLabelledPattern(LabelledPattern* t) {
    } // abstract class
    void VisitTypeCheck::visitBinding(Binding* t) {
    } // abstract class
    void VisitTypeCheck::visitExpr(Expr* t) {
    } // abstract class
    void VisitTypeCheck::visitPatternBinding(PatternBinding* t) {
    } // abstract class
    void VisitTypeCheck::visitVariantFieldType(VariantFieldType* t) {
    } // abstract class
    void VisitTypeCheck::visitRecordFieldType(RecordFieldType* t) {
    } // abstract class
    void VisitTypeCheck::visitTyping(Typing* t) {
    } // abstract class
    void VisitTypeCheck::visitPatternCastAs(PatternCastAs* t) {
    } // abstract class
    void VisitTypeCheck::visitTryCastAs(TryCastAs* t) {
    } // abstract class
    void VisitTypeCheck::visitPatternAsc(PatternAsc* t) {
    } // abstract class
    // void VisitTypeCheck::visitTypeAuto(TypeAuto *t) {}                 // abstract class

    void VisitTypeCheck::visitAProgram(AProgram* a_program)
    {
        /* Code For AProgram Goes Here */

        context.SetVariable("true", std::make_shared<TypeCheck::Bool>());
        context.SetVariable("false", std::make_shared<TypeCheck::Bool>());

        context.SetVariable("0", std::make_shared<TypeCheck::Nat>());

        context.SetVariable("succ", std::make_shared<TypeCheck::Function>(
                                     std::make_shared<TypeCheck::Nat>(),
                                     std::make_shared<TypeCheck::Nat>()));

        auto is_zero = std::make_shared<TypeCheck::Function>(
            std::make_shared<TypeCheck::Nat>(),
            std::make_shared<TypeCheck::Bool>());
        context.SetVariable("Nat::iszero", is_zero);

        context.SetVariable("unit", std::make_shared<TypeCheck::Unit>());

        if (a_program->languagedecl_) {
            a_program->languagedecl_->accept(this);
        }
        if (a_program->listextension_) {
            a_program->listextension_->accept(this);
        }
        if (a_program->listdecl_) {
            a_program->listdecl_->accept(this);
        }

        if (!context.hasMainFunction) {
            std::cout << TypeCheck::ERROR_MISSING_MAIN << "\n";
            exit(1);
        }
    }

    void VisitTypeCheck::visitLanguageCore(LanguageCore* language_core)
    {
        /* Code For LanguageCore Goes Here */
    }

    void VisitTypeCheck::visitAnExtension(AnExtension* an_extension)
    {
        /* Code For AnExtension Goes Here */

        if (an_extension->listextensionname_) {
            an_extension->listextensionname_->accept(this);
        }
    }

    void VisitTypeCheck::visitDeclFun(DeclFun* decl_fun)
    {
        /* Code For DeclFun Goes Here */

        context.SetVariable(decl_fun->stellaident_, std::make_shared<TypeCheck::Function>());
        context.EnterScope(decl_fun->stellaident_);

        if (decl_fun->listannotation_) {
            decl_fun->listannotation_->accept(this);
        }
        visitStellaIdent(decl_fun->stellaident_);
        if (decl_fun->listparamdecl_) {
            decl_fun->listparamdecl_->accept(this);
        }
        if (decl_fun->returntype_) {
            decl_fun->returntype_->accept(this);
        }

        context.PushInferenceContext(context.GetCurrentType());

        if (decl_fun->throwtype_) {
            decl_fun->throwtype_->accept(this);
        }
        if (decl_fun->listdecl_) {
            decl_fun->listdecl_->accept(this);
        }
        if (decl_fun->expr_) {
            decl_fun->expr_->accept(this);
        }

        if (decl_fun->stellaident_ == "main") {
            context.VerifyMainFunction(context.GetVariable("main"));
        }

        context.VerifyReturnType(context.GetCurrentType());
        context.LeaveScope();
        context.PopInferenceContext();
    }

    void VisitTypeCheck::visitDeclTypeAlias(DeclTypeAlias* decl_type_alias)
    {
        /* Code For DeclTypeAlias Goes Here */

        visitStellaIdent(decl_type_alias->stellaident_);
        if (decl_type_alias->type_) {
            decl_type_alias->type_->accept(this);
        }
    }

    void VisitTypeCheck::visitDeclExceptionType(DeclExceptionType* decl_exception_type)
    {
        /* Code For DeclExceptionType Goes Here */

        if (decl_exception_type->type_) {
            decl_exception_type->type_->accept(this);
        }

        context.SetExceptionType(context.GetCurrentType());
        context.PopTypeFromStack();
    }

    void VisitTypeCheck::visitDeclExceptionVariant(DeclExceptionVariant* decl_exception_variant)
    {
        /* Code For DeclExceptionVariant Goes Here */

        visitStellaIdent(decl_exception_variant->stellaident_);
        if (decl_exception_variant->type_) {
            decl_exception_variant->type_->accept(this);
        }
    }

    void VisitTypeCheck::visitAssign(Assign* assign)
    {
        /* Code For Assign Goes Here */

        auto typeCheckpoint = context.CreateStackMarker();

        context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());
        if (assign->expr_1) {
            assign->expr_1->accept(this);
        }
        context.PopInferenceContext();

        context.PushInferenceContext(context.GetCurrentType());
        auto referenceType = context.InferReferenceType();
        context.PopInferenceContext();

        context.PushInferenceContext(referenceType);
        if (assign->expr_2) {
            assign->expr_2->accept(this);
        }
        context.PopInferenceContext();

        context.GetTypeSubstack(typeCheckpoint);

        auto assignmentResult = context.GetAssignmentResultType();
        context.UpdateLastType(assignmentResult);
        context.PushTypeToEvaluationStack(assignmentResult);
    }

    void VisitTypeCheck::visitRef(Ref* ref)
    {
        /* Code For Ref Goes Here */

        auto referencedType = context.InferReferenceType();
        context.PushInferenceContext(referencedType);

        if (ref->expr_) {
            ref->expr_->accept(this);
        }

        context.PopInferenceContext();

        auto newReference = context.CreateReferenceType(context.GetCurrentType());

        context.PopTypeFromStack();
        context.UpdateLastType(newReference);
        context.PushTypeToEvaluationStack(newReference);
    }

    void VisitTypeCheck::visitDeref(Deref* deref)
    {
        /* Code For Deref Goes Here */

        auto dereferencedType = context.InferDereferencedType();
        context.PushInferenceContext(dereferencedType);

        if (deref->expr_) {
            deref->expr_->accept(this);
        }

        auto derefed = context.DereferenceType(context.GetCurrentType());

        context.PopTypeFromStack();
        context.UpdateLastType(derefed);
        context.PushTypeToEvaluationStack(derefed);
    }

    void VisitTypeCheck::visitPanic(Panic* panic)
    {
        /* Code For Panic Goes Here */
        auto exp_type = context.handlePanicType();
        context.UpdateLastType(exp_type);
        context.PushTypeToEvaluationStack(exp_type);
    }

    void VisitTypeCheck::visitThrow(Throw* throw_)
    {
        /* Code For Throw Goes Here */

        auto throwInferenceType = context.InferExceptionType();
        context.PushInferenceContext(throwInferenceType);

        if (throw_->expr_) {
            throw_->expr_->accept(this);
        }

        context.VerifyThrowExpression(context.GetCurrentType());
        context.PopInferenceContext();

        auto exp_type = context.handleThrowableType();
        context.UpdateLastType(exp_type);

        context.PopTypeFromStack();
        context.PushTypeToEvaluationStack(exp_type);
    }

    void VisitTypeCheck::visitTryCatch(TryCatch* try_catch)
    {
        /* Code For TryCatch Goes Here */
        auto typeCheckpoint = context.CreateStackMarker();

        if (try_catch->expr_1) {
            try_catch->expr_1->accept(this);
        }
        auto defaultBranchType = context.GetCurrentType();

        context.PushInferenceContext(context.GetExceptionType());
        context.OpenMatchCase();
        context.InitializePatternMatch(context.GetExceptionType());
        if (try_catch->pattern_) {
            try_catch->pattern_->accept(this);
        }
        context.PopInferenceContext();
        context.RemoveMatchCase();

        bool shouldUpdateInference = false;
        if (context.IsTypeUndefined(context.GetCurrentInferredType())) {
            shouldUpdateInference = true;
            context.PushInferenceContext(defaultBranchType);
        }
        if (try_catch->expr_2) {
            try_catch->expr_2->accept(this);
        }

        context.VerifyTryExpression(context.GetCurrentType());
        if (shouldUpdateInference) {
            context.PopInferenceContext();
        }

        context.UpdateLastType(defaultBranchType);
        context.GetTypeSubstack(typeCheckpoint);
        context.PushTypeToEvaluationStack(defaultBranchType);
    }

    void VisitTypeCheck::visitTryWith(TryWith* try_with)
    {
        /* Code For TryWith Goes Here */
        if (try_with->expr_1) {
            try_with->expr_1->accept(this);
        }
        auto defaultBranchType = context.GetCurrentType();

        bool shouldUpdateInference = false;
        if (context.IsTypeUndefined(context.GetCurrentInferredType())) {
            shouldUpdateInference = true;
            context.PushInferenceContext(defaultBranchType);
        }

        if (try_with->expr_2) {
            try_with->expr_2->accept(this);
        }

        context.VerifyTryExpression(context.GetCurrentType());
        if (shouldUpdateInference) {
            context.PopInferenceContext();
        }

        context.UpdateLastType(defaultBranchType);
        context.PopTypeFromStack();
    }

    void VisitTypeCheck::visitALocalDecl(ALocalDecl* a_local_decl)
    {
        /* Code For ALocalDecl Goes Here */

        if (a_local_decl->decl_) {
            a_local_decl->decl_->accept(this);
        }
    }

    void VisitTypeCheck::visitInlineAnnotation(InlineAnnotation* inline_annotation)
    {
        /* Code For InlineAnnotation Goes Here */
    }

    void VisitTypeCheck::visitAParamDecl(AParamDecl* a_param_decl)
    {
        /* Code For AParamDecl Goes Here */

        visitStellaIdent(a_param_decl->stellaident_);
        if (a_param_decl->type_) {
            a_param_decl->type_->accept(this);
        }

        context.SetVariable(a_param_decl->stellaident_, context.GetCurrentType());
        context.upd_arguments(context.GetCurrentType());
    }

    void VisitTypeCheck::visitNoReturnType(NoReturnType* no_return_type)
    {
        /* Code For NoReturnType Goes Here */
    }

    void VisitTypeCheck::visitSomeReturnType(SomeReturnType* some_return_type)
    {
        /* Code For SomeReturnType Goes Here */

        if (some_return_type->type_) {
            some_return_type->type_->accept(this);
        }

        context.GetCurrentType()->isAscripted = true;
        context.UpdateReturnType(context.GetCurrentType());
    }

    void VisitTypeCheck::visitNoThrowType(NoThrowType* no_throw_type)
    {
        /* Code For NoThrowType Goes Here */
    }

    void VisitTypeCheck::visitSomeThrowType(SomeThrowType* some_throw_type)
    {
        /* Code For SomeThrowType Goes Here */

        if (some_throw_type->listtype_) {
            some_throw_type->listtype_->accept(this);
        }
    }

    void VisitTypeCheck::visitTypeFun(TypeFun* type_fun)
    {
        /* Code For TypeFun Goes Here */
        int typeCheckpoint = context.CreateStackMarker();

        std::string lamda_name = context.generateAnonymousFunctionTag();
        context.SetVariable(lamda_name, std::make_shared<TypeCheck::Function>());
        context.MarkAsLambda(context.GetVariable(lamda_name));
        context.EnterScope(lamda_name);

        if (type_fun->listtype_) {
            type_fun->listtype_->accept(this);
        }

        auto args = context.GetTypeSubstack(typeCheckpoint);
        for (auto& arg : args) {
            context.upd_arguments(arg);
        }

        typeCheckpoint = context.CreateStackMarker();

        if (type_fun->type_) {
            type_fun->type_->accept(this);
            context.UpdateReturnType(context.GetCurrentType());
        }

        context.LeaveScope();
        context.GetTypeSubstack(typeCheckpoint);
        context.UpdateLastType(context.GetVariable(lamda_name));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitTypeRec(TypeRec* type_rec)
    {
        /* Code For TypeRec Goes Here */

        visitStellaIdent(type_rec->stellaident_);
        if (type_rec->type_) {
            type_rec->type_->accept(this);
        }
    }

    void VisitTypeCheck::visitTypeSum(TypeSum* type_sum)
    {
        /* Code For TypeSum Goes Here */
        auto typeCheckpoint = context.CreateStackMarker();

        if (type_sum->type_1) {
            type_sum->type_1->accept(this);
        }
        if (type_sum->type_2) {
            type_sum->type_2->accept(this);
        }

        auto substack = context.GetTypeSubstack(typeCheckpoint);
        std::shared_ptr<TypeCheck::Sum> sum_type = std::make_shared<TypeCheck::Sum>(
            substack[0], substack[1]);

        context.UpdateLastType(sum_type);
        context.PushTypeToEvaluationStack(sum_type);
    }

    void VisitTypeCheck::visitTypeTuple(TypeTuple* type_tuple)
    {
        /* Code For TypeTuple Goes Here */
        int typeCheckpoint = context.CreateStackMarker();

        if (type_tuple->listtype_) {
            type_tuple->listtype_->accept(this);
        }

        auto substack = context.GetTypeSubstack(typeCheckpoint);
        auto tupleInstance = std::make_shared<TypeCheck::Tuple>(substack);

        context.UpdateLastType(tupleInstance);
        context.PushTypeToEvaluationStack(tupleInstance);
    }

    void VisitTypeCheck::visitTypeRecord(TypeRecord* type_record)
    {
        /* Code For TypeRecord Goes Here */
        int typeCheckpoint = context.CreateStackMarker();
        int fieldCollectionPoint = context.StartFieldCollection();

        if (type_record->listrecordfieldtype_) {
            type_record->listrecordfieldtype_->accept(this);
        }

        auto typeSubstitutions = context.GetTypeSubstack(typeCheckpoint);
        auto collectedFields = context.GetFieldSubstack(fieldCollectionPoint);

        auto recordInstance = std::make_shared<TypeCheck::Record>(typeSubstitutions, collectedFields);

        context.UpdateLastType(recordInstance);
        context.PushTypeToEvaluationStack(recordInstance);
    }

    void VisitTypeCheck::visitTypeVariant(TypeVariant* type_variant)
    {
        /* Code For TypeVariant Goes Here */
        int typeCheckpoint = context.CreateStackMarker();
        int fieldCollectionPoint = context.StartFieldCollection();

        if (type_variant->listvariantfieldtype_) {
            type_variant->listvariantfieldtype_->accept(this);
        }

        auto typeSubstitutions = context.GetTypeSubstack(typeCheckpoint);
        auto collectedFields = context.GetFieldSubstack(fieldCollectionPoint);

        auto new_variant = std::make_shared<TypeCheck::Variant>(typeSubstitutions, collectedFields);

        context.UpdateLastType(new_variant);
        context.PushTypeToEvaluationStack(new_variant);
        context.SetCurrentEntityName("");
    }

    void VisitTypeCheck::visitTypeList(TypeList* type_list)
    {
        /* Code For TypeList Goes Here */

        if (type_list->type_) {
            type_list->type_->accept(this);
        }

        auto currentInnerType = context.GetCurrentType();
        context.PopTypeFromStack();

        context.UpdateLastType(std::make_shared<TypeCheck::List>(currentInnerType));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitTypeBool(TypeBool* type_bool)
    {
        /* Code For TypeBool Goes Here */
        context.UpdateLastType(std::make_shared<TypeCheck::Bool>());
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitTypeNat(TypeNat* type_nat)
    {
        /* Code For TypeNat Goes Here */
        context.UpdateLastType(std::make_shared<TypeCheck::Nat>());
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitTypeUnit(TypeUnit* type_unit)
    {
        /* Code For TypeUnit Goes Here */
        context.UpdateLastType(std::make_shared<TypeCheck::Unit>());
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitTypeAuto(TypeAuto* type_auto) {
        context.UpdateLastType(std::make_shared<TypeCheck::TypeAuto>());
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitTypeTop(TypeTop* type_top)
    {
        /* Code For TypeTop Goes Here */
        auto topTypeInstance = std::make_shared<TypeCheck::Top>();

        context.UpdateLastType(topTypeInstance);
        context.PushTypeToEvaluationStack(topTypeInstance);
    }

    void VisitTypeCheck::visitTypeBottom(TypeBottom* type_bottom)
    {
        /* Code For TypeBottom Goes Here */
        auto bottomTypeInstance = std::make_shared<TypeCheck::Bottom>();

        context.UpdateLastType(bottomTypeInstance);
        context.PushTypeToEvaluationStack(bottomTypeInstance);
    }

    void VisitTypeCheck::visitTypeRef(TypeRef* type_ref)
    {
        /* Code For TypeRef Goes Here */

        std::shared_ptr<TypeCheck::Ref> referenceTypeInstance;

        if (type_ref->type_) {
            type_ref->type_->accept(this);
        }

        referenceTypeInstance = std::make_shared<TypeCheck::Ref>(context.GetCurrentType());

        context.PopTypeFromStack();
        context.UpdateLastType(referenceTypeInstance);
        context.PushTypeToEvaluationStack(referenceTypeInstance);
    }

    void VisitTypeCheck::visitTypeVar(TypeVar* type_var)
    {
        /* Code For TypeVar Goes Here */

        visitStellaIdent(type_var->stellaident_);

        auto universalType = context.ResolveUniversalType(type_var->stellaident_);
        context.UpdateLastType(universalType);
        context.PushTypeToEvaluationStack(universalType);
    }

    void VisitTypeCheck::visitAMatchCase(AMatchCase* a_match_case)
    {
        /* Code For AMatchCase Goes Here */
        context.SetCurrentEntityName("");

        if (a_match_case->pattern_) {
            a_match_case->pattern_->accept(this);
        }
        auto patternBindingName = context.GetCurrentEntityName();
        auto patternVariableType = context.GetMatchedVariable();

        if (patternBindingName != context.MATCH_ANY && patternBindingName != "") {
            context.SetVariable(patternBindingName, patternVariableType);
        }

        context.VerifyExhaustiveness();

        auto expectedCaseType = context.GetCurrentInferredType();
        context.PopInferenceContext();

        if (a_match_case->expr_) {
            a_match_case->expr_->accept(this);
        }

        context.PushInferenceContext(expectedCaseType);
        context.ResetPatternMatching();
    }

    void VisitTypeCheck::visitNoTyping(NoTyping* no_typing)
    {
        /* Code For NoTyping Goes Here */
        auto empty = std::make_shared<TypeCheck::Unknown>();

        context.UpdateLastType(empty);
        context.PushTypeToEvaluationStack(empty);
    }

    void VisitTypeCheck::visitSomeTyping(SomeTyping* some_typing)
    {
        /* Code For SomeTyping Goes Here */

        if (some_typing->type_) {
            some_typing->type_->accept(this);
        }
    }

    void VisitTypeCheck::visitNoPatternData(NoPatternData* no_pattern_data)
    {
        /* Code For NoPatternData Goes Here */
    }

    void VisitTypeCheck::visitSomePatternData(SomePatternData* some_pattern_data)
    {
        /* Code For SomePatternData Goes Here */

        if (some_pattern_data->pattern_) {
            some_pattern_data->pattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitNoExprData(NoExprData* no_expr_data)
    {
        /* Code For NoExprData Goes Here */
        auto empty = std::make_shared<TypeCheck::Unknown>();

        context.UpdateLastType(empty);
        context.PushTypeToEvaluationStack(empty);
    }

    void VisitTypeCheck::visitSomeExprData(SomeExprData* some_expr_data)
    {
        /* Code For SomeExprData Goes Here */

        if (some_expr_data->expr_) {
            some_expr_data->expr_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternVariant(PatternVariant* pattern_variant)
    {
        /* Code For PatternVariant Goes Here */
        context.MatchVariantPattern(pattern_variant->stellaident_);

        visitStellaIdent(pattern_variant->stellaident_);
        if (pattern_variant->patterndata_) {
            pattern_variant->patterndata_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternInl(PatternInl* pattern_inl)
    {
        /* Code For PatternInl Goes Here */

        context.MatchInlPattern();
        if (pattern_inl->pattern_) {
            pattern_inl->pattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternInr(PatternInr* pattern_inr)
    {
        /* Code For PatternInr Goes Here */

        context.MatchInrPattern();
        if (pattern_inr->pattern_) {
            pattern_inr->pattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternTuple(PatternTuple* pattern_tuple)
    {
        /* Code For PatternTuple Goes Here */

        if (pattern_tuple->listpattern_) {
            pattern_tuple->listpattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternRecord(PatternRecord* pattern_record)
    {
        /* Code For PatternRecord Goes Here */

        if (pattern_record->listlabelledpattern_) {
            pattern_record->listlabelledpattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternList(PatternList* pattern_list)
    {
        /* Code For PatternList Goes Here */

        if (pattern_list->listpattern_) {
            pattern_list->listpattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternCons(PatternCons* pattern_cons)
    {
        /* Code For PatternCons Goes Here */

        if (pattern_cons->pattern_1) {
            pattern_cons->pattern_1->accept(this);
        }
        if (pattern_cons->pattern_2) {
            pattern_cons->pattern_2->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternFalse(PatternFalse* pattern_false)
    {
        /* Code For PatternFalse Goes Here */
        context.MatchFalsePattern();
    }

    void VisitTypeCheck::visitPatternTrue(PatternTrue* pattern_true)
    {
        /* Code For PatternTrue Goes Here */
        context.MatchTruePattern();
    }

    void VisitTypeCheck::visitPatternUnit(PatternUnit* pattern_unit)
    {
        /* Code For PatternUnit Goes Here */
        context.MatchUnitPattern();
    }

    void VisitTypeCheck::visitPatternInt(PatternInt* pattern_int)
    {
        /* Code For PatternInt Goes Here */
        context.MatchIntPattern();
        visitInteger(pattern_int->integer_);
    }

    void VisitTypeCheck::visitPatternSucc(PatternSucc* pattern_succ)
    {
        /* Code For PatternSucc Goes Here */
        context.MatchSuccPattern();
        if (pattern_succ->pattern_) {
            pattern_succ->pattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitPatternVar(PatternVar* pattern_var)
    {
        /* Code For PatternVar Goes Here */

        context.SetCurrentEntityName(pattern_var->stellaident_);
        if (pattern_var->stellaident_ == context.MATCH_ANY) {
            context.MatchAnyPattern();
        }
        visitStellaIdent(pattern_var->stellaident_);
    }

    void VisitTypeCheck::visitALabelledPattern(ALabelledPattern* a_labelled_pattern)
    {
        /* Code For ALabelledPattern Goes Here */

        visitStellaIdent(a_labelled_pattern->stellaident_);
        if (a_labelled_pattern->pattern_) {
            a_labelled_pattern->pattern_->accept(this);
        }
    }

    void VisitTypeCheck::visitABinding(ABinding* a_binding)
    {
        /* Code For ABinding Goes Here */

        std::string bindingName = a_binding->stellaident_;
        visitStellaIdent(a_binding->stellaident_);

        auto inf_type = context.InferFieldType(bindingName);
        context.PushInferenceContext(inf_type);

        if (a_binding->expr_) {
            a_binding->expr_->accept(this);
        }

        context.PopInferenceContext();
        context.DefineRecordField(bindingName, context.GetCurrentType());
    }

    void VisitTypeCheck::visitSequence(Sequence* sequence)
    {
        /* Code For Sequence Goes Here */
        auto typeCheckpoint = context.CreateStackMarker();

        context.PushInferenceContext(context.InferSequenceType());
        if (sequence->expr_1) {
            sequence->expr_1->accept(this);
        }
        context.PopInferenceContext();

        if (sequence->expr_2) {
            sequence->expr_2->accept(this);
        }

        auto result = context.GetCurrentType();
        context.GetTypeSubstack(typeCheckpoint);

        context.PushTypeToEvaluationStack(result);
    }

    void VisitTypeCheck::visitIf(If* if_)
    {
        /* Code For If Goes Here */
        int typeCheckpoint = context.CreateStackMarker();

        context.PushInferenceContext(context.GetVariable("true"));
        if (if_->expr_1) {
            if_->expr_1->accept(this);
        }
        auto condition = context.GetCurrentType();
        context.PopInferenceContext();

        if (if_->expr_2) {
            if_->expr_2->accept(this);
        }
        auto trueBranchType = context.GetCurrentType();

        bool shouldUpdateInference = false;
        if (context.IsTypeUndefined(context.GetCurrentInferredType())) {
            shouldUpdateInference = true;
            context.PushInferenceContext(trueBranchType);
        }

        if (if_->expr_3) {
            if_->expr_3->accept(this);
        }

        if (shouldUpdateInference) {
            context.PopInferenceContext();
        }
        auto elseBranchType = context.GetCurrentType();

        context.VerifyIfExpression(condition, trueBranchType, elseBranchType);

        context.UpdateLastType(trueBranchType);
        context.GetTypeSubstack(typeCheckpoint);
        context.PushTypeToEvaluationStack(trueBranchType);
    }

    void VisitTypeCheck::visitLet(Let* let)
    {
        /* Code For Let Goes Here */
        auto letBindingName = context.generateLetBindingIdentifier();
        context.SetVariable(letBindingName, std::make_shared<TypeCheck::Unknown>());
        context.EnterScope(letBindingName);

        context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());
        if (let->listpatternbinding_) {
            let->listpatternbinding_->accept(this);
        }
        context.PopInferenceContext();

        if (let->expr_) {
            let->expr_->accept(this);
        }

        auto letBindingType = context.GetCurrentType();
        letBindingType->isAscripted = true;

        context.LeaveScope();
        context.UpdateVariableType(letBindingName, letBindingType);
        context.UpdateLastType(letBindingType);
    }

    void VisitTypeCheck::visitLetRec(LetRec* let_rec)
    {
        /* Code For LetRec Goes Here */

        if (let_rec->listpatternbinding_) {
            let_rec->listpatternbinding_->accept(this);
        }
        if (let_rec->expr_) {
            let_rec->expr_->accept(this);
        }
    }

    void VisitTypeCheck::visitLessThan(LessThan* less_than)
    {
        /* Code For LessThan Goes Here */

        if (less_than->expr_1) {
            less_than->expr_1->accept(this);
        }
        if (less_than->expr_2) {
            less_than->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitLessThanOrEqual(LessThanOrEqual* less_than_or_equal)
    {
        /* Code For LessThanOrEqual Goes Here */

        if (less_than_or_equal->expr_1) {
            less_than_or_equal->expr_1->accept(this);
        }
        if (less_than_or_equal->expr_2) {
            less_than_or_equal->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitGreaterThan(GreaterThan* greater_than)
    {
        /* Code For GreaterThan Goes Here */

        if (greater_than->expr_1) {
            greater_than->expr_1->accept(this);
        }
        if (greater_than->expr_2) {
            greater_than->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitGreaterThanOrEqual(GreaterThanOrEqual* greater_than_or_equal)
    {
        /* Code For GreaterThanOrEqual Goes Here */

        if (greater_than_or_equal->expr_1) {
            greater_than_or_equal->expr_1->accept(this);
        }
        if (greater_than_or_equal->expr_2) {
            greater_than_or_equal->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitEqual(Equal* equal)
    {
        /* Code For Equal Goes Here */

        if (equal->expr_1) {
            equal->expr_1->accept(this);
        }
        if (equal->expr_2) {
            equal->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitNotEqual(NotEqual* not_equal)
    {
        /* Code For NotEqual Goes Here */

        if (not_equal->expr_1) {
            not_equal->expr_1->accept(this);
        }
        if (not_equal->expr_2) {
            not_equal->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitTypeAsc(TypeAsc* type_asc)
    {
        /* Code For TypeAsc Goes Here */
        auto typeCheckpoint = context.CreateStackMarker();

        if (type_asc->type_) {
            type_asc->type_->accept(this);
        }
        auto as_type = context.GetCurrentType();

        context.PushInferenceContext(as_type);

        if (type_asc->expr_) {
            type_asc->expr_->accept(this);
        }
        auto expr_type = context.GetCurrentType();

        context.PopInferenceContext();

        context.VerifyTypeAscription(expr_type, as_type);
        context.GetTypeSubstack(typeCheckpoint);

        context.UpdateLastType(as_type);
        context.PushTypeToEvaluationStack(as_type);
    }

    void VisitTypeCheck::visitTypeCast(TypeCast* type_cast)
    {
        /* Code For TypeCast Goes Here */

        context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());

        if (type_cast->expr_) {
            type_cast->expr_->accept(this);
        }
        context.PopInferenceContext();

        auto casted = context.GetCurrentType();
        context.PopTypeFromStack();

        if (type_cast->type_) {
            type_cast->type_->accept(this);
        }
    }

    void VisitTypeCheck::visitAbstraction(Abstraction* abstraction)
    {
        /* Code For Abstraction Goes Here */
        int typeCheckpoint = context.CreateStackMarker();

        std::string lamda_name = context.generateAnonymousFunctionTag();
        context.SetVariable(lamda_name, std::make_shared<TypeCheck::Function>());
        context.MarkAsLambda(context.GetVariable(lamda_name));
        context.EnterScope(lamda_name);

        if (abstraction->listparamdecl_) {
            abstraction->listparamdecl_->accept(this);
        }

        auto lambdaReturnType = context.InferLambdaReturnType(lamda_name);
        context.PushInferenceContext(lambdaReturnType);

        if (abstraction->expr_) {
            abstraction->expr_->accept(this);
            context.UpdateReturnType(context.GetCurrentType());
        }
        context.PopInferenceContext();

        context.LeaveScope();
        context.GetTypeSubstack(typeCheckpoint);
        context.UpdateLastType(context.GetVariable(lamda_name));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitVariant(Variant* variant)
    {
        /* Code For Variant Goes Here */
        auto inf_type = context.InferVariantType(variant->stellaident_);

        visitStellaIdent(variant->stellaident_);

        context.PushInferenceContext(inf_type);
        if (variant->exprdata_) {
            variant->exprdata_->accept(this);
        }
        context.PopInferenceContext();

        auto new_variant = context.CreateVariant(variant->stellaident_, context.GetCurrentType());

        context.PopTypeFromStack();
        context.UpdateLastType(new_variant);
        context.PushTypeToEvaluationStack(new_variant);
    }

    void VisitTypeCheck::visitMatch(Match* match)
    {
        /* Code For Match Goes Here */

        auto match_name = context.generatePatternMatchingLabel();
        context.SetVariable(match_name, std::make_shared<TypeCheck::Unknown>());
        context.EnterScope(match_name);
        context.OpenMatchCase();

        context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());
        if (match->expr_) {
            match->expr_->accept(this);
        }
        context.PopInferenceContext();
        auto init_expr = context.GetCurrentType();
        context.InitializePatternMatch(init_expr);
        context.PopTypeFromStack();

        auto typeCheckpoint = context.CreateStackMarker();
        context.PushInferenceContext(init_expr);
        if (match->listmatchcase_) {
            match->listmatchcase_->accept(this);
        }
        context.PopInferenceContext();

        auto match_types = context.GetTypeSubstack(typeCheckpoint);

        context.ValidatePatternMatching(match_types);

        auto result_type = context.GetCurrentType();
        context.close_match();
        context.LeaveScope();

        context.PushTypeToEvaluationStack(result_type);
        context.UpdateVariableType(match_name, result_type);
        context.UpdateLastType(result_type);
    }

    void VisitTypeCheck::visitList(List* list)
    {
        /* Code For List Goes Here */
        auto typeCheckpoint = context.CreateStackMarker();
        auto currentInnerType = context.InferListElementType();
        context.PushInferenceContext(currentInnerType);

        context.ScheduleTypeInferences(0);

        if (list->listexpr_) {
            list->listexpr_->accept(this);
        }

        context.ClearInferenceSchedule();

        auto substack = context.GetTypeSubstack(typeCheckpoint);
        context.VerifyListInitialization(substack);

        context.PopInferenceContext();

        auto new_list = std::make_shared<TypeCheck::List>(context.GetCurrentType());

        context.UpdateLastType(new_list);
        context.PushTypeToEvaluationStack(new_list);
    }

    void VisitTypeCheck::visitAdd(Add* add)
    {
        /* Code For Add Goes Here */

        if (add->expr_1) {
            add->expr_1->accept(this);
        }
        if (add->expr_2) {
            add->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitSubtract(Subtract* subtract)
    {
        /* Code For Subtract Goes Here */

        if (subtract->expr_1) {
            subtract->expr_1->accept(this);
        }
        if (subtract->expr_2) {
            subtract->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitLogicOr(LogicOr* logic_or)
    {
        /* Code For LogicOr Goes Here */

        if (logic_or->expr_1) {
            logic_or->expr_1->accept(this);
        }
        if (logic_or->expr_2) {
            logic_or->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitMultiply(Multiply* multiply)
    {
        /* Code For Multiply Goes Here */

        if (multiply->expr_1) {
            multiply->expr_1->accept(this);
        }
        if (multiply->expr_2) {
            multiply->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitDivide(Divide* divide)
    {
        /* Code For Divide Goes Here */

        if (divide->expr_1) {
            divide->expr_1->accept(this);
        }
        if (divide->expr_2) {
            divide->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitLogicAnd(LogicAnd* logic_and)
    {
        /* Code For LogicAnd Goes Here */

        if (logic_and->expr_1) {
            logic_and->expr_1->accept(this);
        }
        if (logic_and->expr_2) {
            logic_and->expr_2->accept(this);
        }
    }

    void VisitTypeCheck::visitApplication(Application* application)
    {
        /* Code For Application Goes Here */
        std::shared_ptr<TypeCheck::Function> lambda = nullptr;
        int typeCheckpoint = context.CreateStackMarker();

        context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());
        if (application->expr_) {
            application->expr_->accept(this);

            if (
                !context.GetVariable(context.GetCurrentEntityName()) && (context.IsFunctionType(context.GetCurrentType()) || context.CanCreateLambdaType(context.GetCurrentType()))) {
                auto lambdaId = context.generateAnonymousFunctionTag();

                context.SetVariable(lambdaId, context.GetCurrentType());
                context.SetCurrentEntityName(lambdaId);
            }
        }
        context.PopInferenceContext();
        auto functionName = context.GetCurrentEntityName();

        context.VerifyFunctionApplication(functionName);

        context.GetTypeSubstack(typeCheckpoint);

        context.PushApplication(functionName);
        auto argumentTypes = context.InferFunctionArguments(functionName);

        context.SetCurrentEntityName("");

        typeCheckpoint = context.CreateStackMarker();
        for (int sch = argumentTypes.size() - 1; sch >= 0; sch--) {
            context.PushInferenceContext(argumentTypes[sch]);
        }

        if (application->listexpr_) {
            application->listexpr_->accept(this);
        }

        if (!context.IsInferenceScheduleEmpty()) {
            std::cout << TypeCheck::ERROR_INCORRECT_NUMBER_OF_ARGUMENTS << "\n";
            exit(1);
        }

        context.ClearInferenceSchedule();

        context.SetCurrentEntityName("");

        auto lst_t = context.ApplyFunction(context.PopApplication(), context.GetTypeSubstack(typeCheckpoint));
        context.UpdateLastType(lst_t);
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitDotRecord(DotRecord* dot_record)
    {
        /* Code For DotRecord Goes Here */
        context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());

        if (dot_record->expr_) {
            dot_record->expr_->accept(this);
        }
        auto record = context.GetCurrentType();
        context.PopInferenceContext();

        visitStellaIdent(dot_record->stellaident_);
        std::string typeId = dot_record->stellaident_;

        auto accessed = context.AccessMember(record, typeId);

        context.UpdateLastType(accessed);
        context.PopTypeFromStack();
        context.PushTypeToEvaluationStack(accessed);
    }

    void VisitTypeCheck::visitDotTuple(DotTuple* dot_tuple)
    {
        /* Code For DotTuple Goes Here */
        context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());

        if (dot_tuple->expr_) {
            dot_tuple->expr_->accept(this);
        }
        auto tuple = context.GetCurrentType();
        context.PopInferenceContext();

        visitInteger(dot_tuple->integer_);
        auto typeId = context.GetLastInteger();

        auto accessed = context.AccessMember(tuple, typeId);

        context.UpdateLastType(accessed);
        context.PopTypeFromStack();
        context.PushTypeToEvaluationStack(accessed);
    }

    void VisitTypeCheck::visitTuple(Tuple* tuple)
    {
        /* Code For Tuple Goes Here */
        int typeCheckpoint = context.CreateStackMarker();
        auto tupleComponents = context.InferTupleComponents();
        for (int sch = tupleComponents.size() - 1; sch >= 0; sch--) {
            context.PushInferenceContext(tupleComponents[sch]);
        }

        if (context.GetScheduledInferenceCount() == context.UNKNOWN_SCH) {
            context.PushInferenceContext(std::make_shared<TypeCheck::Unknown>());
        }

        if (tuple->listexpr_) {
            tuple->listexpr_->accept(this);
        }

        if (!context.IsInferenceScheduleEmpty() && !context.GetScheduledInferenceCount() == context.UNKNOWN_SCH) {
            std::cout << TypeCheck::ERROR_UNEXPECTED_TUPLE_LENGTH << "\n";
            exit(1);
        }

        if (context.GetScheduledInferenceCount() == context.UNKNOWN_SCH) {
            context.PopInferenceContext();
        }

        context.ClearInferenceSchedule();

        auto substack = context.GetTypeSubstack(typeCheckpoint);
        auto tupleInstance = std::make_shared<TypeCheck::Tuple>(substack);

        context.UpdateLastType(tupleInstance);
        context.PushTypeToEvaluationStack(tupleInstance);
    }

    void VisitTypeCheck::visitRecord(Record* record)
    {
        /* Code For Record Goes Here */
        int typeCheckpoint = context.CreateStackMarker();
        auto recordInstance = context.InferRecordType();

        context.PushInferenceContext(recordInstance);

        if (record->listbinding_) {
            record->listbinding_->accept(this);
        }

        context.VerifyRecordType(recordInstance);
        context.PopInferenceContext();

        context.GetTypeSubstack(typeCheckpoint);
        context.UpdateLastType(recordInstance);
        context.PushTypeToEvaluationStack(recordInstance);
    }

    void VisitTypeCheck::visitConsList(ConsList* cons_list)
    {
        /* Code For ConsList Goes Here */

        auto currentInnerType = context.InferListElementType();

        auto typeCheckpoint = context.CreateStackMarker();

        context.PushInferenceContext(currentInnerType);
        if (cons_list->expr_1) {
            cons_list->expr_1->accept(this);
        }
        context.PopInferenceContext();

        auto containerType = context.InferFromConstructor(context.GetCurrentType());
        context.PushInferenceContext(containerType);
        if (cons_list->expr_2) {
            cons_list->expr_2->accept(this);
        }
        context.PopInferenceContext();

        auto constructorComponents = context.GetTypeSubstack(typeCheckpoint);
        if (constructorComponents.size() != 2) {
            std::cout << TypeCheck::ERROR_UNEXPECTED_TYPE_FOR_EXPRESSION << "\n";
            exit(1);
        }

        context.VerifyConstructor(constructorComponents[0], constructorComponents[1]);

        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitHead(Head* head)
    {
        /* Code For Head Goes Here */
        auto containerType = context.InferListContainer();
        context.PushInferenceContext(containerType);

        if (head->expr_) {
            head->expr_->accept(this);
        }

        auto listType = context.GetCurrentType();
        context.PopTypeFromStack();

        context.VerifyHeadElement(listType);
        context.PopInferenceContext();

        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitIsEmpty(IsEmpty* is_empty)
    {
        /* Code For IsEmpty Goes Here */
        auto emptyListType = context.InferEmptyList();
        context.PushInferenceContext(emptyListType);

        if (is_empty->expr_) {
            is_empty->expr_->accept(this);
        }

        auto listType = context.GetCurrentType();
        context.PopTypeFromStack();

        context.VerifyEmptyList(listType);
        context.PopInferenceContext();

        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitTail(Tail* tail)
    {
        /* Code For Tail Goes Here */
        auto inf_lst_type = context.InferListStructure();
        context.PushInferenceContext(inf_lst_type);

        if (tail->expr_) {
            tail->expr_->accept(this);
        }

        auto listType = context.GetCurrentType();
        context.PopTypeFromStack();

        context.verify_tail(listType);
        context.PopInferenceContext();

        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitInl(Inl* inl)
    {
        /* Code For Inl Goes Here */
        auto currentInnerType = context.InferLeftInjection();
        context.PushInferenceContext(currentInnerType);

        if (inl->expr_) {
            inl->expr_->accept(this);
        }

        context.PopInferenceContext();

        auto inl_expr = context.GetCurrentType();
        std::shared_ptr<TypeCheck::Sum> sum_type = std::make_shared<TypeCheck::Sum>(false, inl_expr);

        context.VerifySumType(sum_type);

        context.PopTypeFromStack();
        context.UpdateLastType(sum_type);
        context.PushTypeToEvaluationStack(sum_type);
    }

    void VisitTypeCheck::visitInr(Inr* inr)
    {
        /* Code For Inr Goes Here */
        auto currentInnerType = context.InferRightInjection();
        context.PushInferenceContext(currentInnerType);

        if (inr->expr_) {
            inr->expr_->accept(this);
        }

        context.PopInferenceContext();

        auto inl_expr = context.GetCurrentType();
        std::shared_ptr<TypeCheck::Sum> sum_type = std::make_shared<TypeCheck::Sum>(true, inl_expr);

        context.VerifySumType(sum_type);

        context.PopTypeFromStack();
        context.UpdateLastType(sum_type);
        context.PushTypeToEvaluationStack(sum_type);
    }

    void VisitTypeCheck::visitSucc(Succ* succ)
    {
        /* Code For Succ Goes Here */

        if (succ->expr_) {
            succ->expr_->accept(this);
        }

        auto lst_t = context.GetCurrentType();

        context.PopTypeFromStack();
        context.UpdateLastType(context.ApplyFunction("succ", lst_t));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitLogicNot(LogicNot* logic_not)
    {
        /* Code For LogicNot Goes Here */

        if (logic_not->expr_) {
            logic_not->expr_->accept(this);
        }
    }

    void VisitTypeCheck::visitPred(Pred* pred)
    {
        /* Code For Pred Goes Here */

        if (pred->expr_) {
            pred->expr_->accept(this);
        }
    }

    void VisitTypeCheck::visitIsZero(IsZero* is_zero)
    {
        /* Code For IsZero Goes Here */

        context.PushInferenceContext(context.GetVariable("0"));
        if (is_zero->expr_) {
            is_zero->expr_->accept(this);
        }
        context.PopInferenceContext();

        auto lst_t = context.GetCurrentType();

        context.PopTypeFromStack();
        context.UpdateLastType(context.ApplyFunction("Nat::iszero", lst_t));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitFix(Fix* fix)
    {
        /* Code For Fix Goes Here */
        auto inf_func = context.InferFixedPoint();
        context.PushInferenceContext(inf_func);

        if (fix->expr_) {
            fix->expr_->accept(this);
        }

        context.PopInferenceContext();

        context.ValidateFixpoint(context.GetCurrentType());
        auto fixedPointResult = context.ApplyFixedFunction(context.GetCurrentType());

        context.PopTypeFromStack();
        context.UpdateLastType(fixedPointResult);
        context.PushTypeToEvaluationStack(fixedPointResult);

        if (context.IsFunctionType(fixedPointResult)) {
            std::string fixedPointId = context.generateAnonymousFunctionTag();
            context.SetVariable(fixedPointId, fixedPointResult);
            context.PushApplication(fixedPointId);
            context.SetCurrentEntityName(fixedPointId);
        }
    }

    void VisitTypeCheck::visitNatRec(NatRec* nat_rec)
    {
        /* Code For NatRec Goes Here */
        int typeCheckpoint = context.CreateStackMarker();

        context.PushInferenceContext(std::shared_ptr<TypeCheck::Nat>());
        if (nat_rec->expr_1) {
            nat_rec->expr_1->accept(this);
        }
        auto rec_counter = context.GetCurrentType();
        context.PopInferenceContext();

        if (nat_rec->expr_2) {
            nat_rec->expr_2->accept(this);
        }
        auto rec_init = context.GetCurrentType();

        auto infer_lambda = context.InferInsideRecord();
        context.PushInferenceContext(infer_lambda);
        if (nat_rec->expr_3) {
            nat_rec->expr_3->accept(this);
        }
        auto rec = context.GetCurrentType();
        context.PopInferenceContext();

        context.VerifyRecursiveType(rec_counter, rec_init, rec);

        context.UpdateLastType(rec_init);
        context.GetTypeSubstack(typeCheckpoint);
        context.PushTypeToEvaluationStack(rec_init);
    }

    void VisitTypeCheck::visitFold(Fold* fold)
    {
        /* Code For Fold Goes Here */

        if (fold->type_) {
            fold->type_->accept(this);
        }
        if (fold->expr_) {
            fold->expr_->accept(this);
        }
    }

    void VisitTypeCheck::visitUnfold(Unfold* unfold)
    {
        /* Code For Unfold Goes Here */

        if (unfold->type_) {
            unfold->type_->accept(this);
        }
        if (unfold->expr_) {
            unfold->expr_->accept(this);
        }
    }

    void VisitTypeCheck::visitConstTrue(ConstTrue* const_true)
    {
        /* Code For ConstTrue Goes Here */
        context.UpdateLastType(context.GetVariable("true"));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitConstFalse(ConstFalse* const_false)
    {
        /* Code For ConstFalse Goes Here */
        context.UpdateLastType(context.GetVariable("false"));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitConstUnit(ConstUnit* const_unit)
    {
        /* Code For ConstUnit Goes Here */
        context.UpdateLastType(context.GetVariable("unit"));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
    }

    void VisitTypeCheck::visitConstInt(ConstInt* const_int)
    {
        /* Code For ConstInt Goes Here */

        context.UpdateLastType(context.GetVariable("0"));
        context.PushTypeToEvaluationStack(context.GetCurrentType());
        visitInteger(const_int->integer_);
        context.VerifyInt(context.GetLastInteger());
    }

    void VisitTypeCheck::visitConstMemory(ConstMemory* const_memory)
    {
        /* Code For ConstMemory Goes Here */

        auto mem_alloc = context.InferMemoryReferenceType();

        visitMemoryAddress(const_memory->memoryaddress_);

        context.UpdateLastType(mem_alloc);
        context.PushTypeToEvaluationStack(mem_alloc);
    }

    void VisitTypeCheck::visitVar(Var* var)
    {
        /* Code For Var Goes Here */
        if (context.GetLValueState()) {
            context.SetCurrentEntityName(var->stellaident_);
            return;
        }

        auto var_type = context.GetVariable(var->stellaident_);
        if (!var_type) {
            std::cout << TypeCheck::ERROR_UNDEFINED_VARIABLE << "\n";
            exit(1);
        }

        context.SetCurrentEntityName(var->stellaident_);
        context.UpdateLastType(var_type);
        context.PushTypeToEvaluationStack(context.GetCurrentType());
        visitStellaIdent(var->stellaident_);
    }

    void VisitTypeCheck::visitAPatternBinding(APatternBinding* a_pattern_binding)
    {
        /* Code For APatternBinding Goes Here */

        context.SetLValueState(true);
        std::string letBindingName = "undef";
        if (a_pattern_binding->pattern_) {
            a_pattern_binding->pattern_->accept(this);
            letBindingName = context.GetCurrentEntityName();
            context.SetCurrentEntityName("");
        }

        context.SetLValueState(false);

        if (a_pattern_binding->expr_) {
            a_pattern_binding->expr_->accept(this);
        }

        context.SetVariable(letBindingName, context.GetCurrentType());
    }

    void VisitTypeCheck::visitAVariantFieldType(AVariantFieldType* a_variant_field_type)
    {
        /* Code For AVariantFieldType Goes Here */

        visitStellaIdent(a_variant_field_type->stellaident_);
        if (a_variant_field_type->optionaltyping_) {
            a_variant_field_type->optionaltyping_->accept(this);
        }

        context.SetCurrentEntityName(a_variant_field_type->stellaident_);
        context.PushFieldToBuffer(a_variant_field_type->stellaident_);
    }

    void VisitTypeCheck::visitARecordFieldType(ARecordFieldType* a_record_field_type)
    {
        /* Code For ARecordFieldType Goes Here */
        std::string bindingName = a_record_field_type->stellaident_;

        visitStellaIdent(a_record_field_type->stellaident_);
        if (a_record_field_type->type_) {
            a_record_field_type->type_->accept(this);
        }

        context.PushFieldToBuffer(bindingName);
    }

    void VisitTypeCheck::visitATyping(ATyping* a_typing)
    {
        /* Code For ATyping Goes Here */

        if (a_typing->expr_) {
            a_typing->expr_->accept(this);
        }
        if (a_typing->type_) {
            a_typing->type_->accept(this);
        }
    }

    void VisitTypeCheck::visitListStellaIdent(ListStellaIdent* list_stella_ident)
    {
        for (const auto& i : *list_stella_ident)
        {
            visitStellaIdent(i);
        }
    }

    void VisitTypeCheck::visitListExtensionName(ListExtensionName* list_extension_name)
    {
        for (const auto& i : *list_extension_name)
        {
            visitExtensionName(i);
        }
    }

    void VisitTypeCheck::visitListExtension(ListExtension* list_extension)
    {
        for (const auto& i : *list_extension)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListDecl(ListDecl* list_decl)
    {
        for (const auto& i : *list_decl)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListLocalDecl(ListLocalDecl* list_local_decl)
    {
        for (const auto& i : *list_local_decl)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListAnnotation(ListAnnotation* list_annotation)
    {
        for (const auto& i : *list_annotation)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListParamDecl(ListParamDecl* list_param_decl)
    {
        for (const auto& i : *list_param_decl)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListType(ListType* list_type)
    {
        for (const auto& i : *list_type)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListMatchCase(ListMatchCase* list_match_case)
    {
        for (const auto& i : *list_match_case)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListPattern(ListPattern* list_pattern)
    {
        for (const auto& i : *list_pattern)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListLabelledPattern(ListLabelledPattern* list_labelled_pattern)
    {
        for (const auto& i : *list_labelled_pattern)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListBinding(ListBinding* list_binding)
    {
        for (const auto& i : *list_binding)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListExpr(ListExpr* list_expr)
    {
        for (ListExpr::iterator i = list_expr->begin(); i != list_expr->end(); ++i)
        {
            (*i)->accept(this);

            if (context.HasScheduledInferences()) {
                context.PopInferenceContext();
                context.CompleteScheduledInference();
            } else {
                context.MarkScheduleInvalid();
            }
        }
    }

    void VisitTypeCheck::visitListPatternBinding(ListPatternBinding* list_pattern_binding)
    {
        for (const auto& i : *list_pattern_binding)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListVariantFieldType(ListVariantFieldType* list_variant_field_type)
    {
        for (const auto& i : *list_variant_field_type)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitListRecordFieldType(ListRecordFieldType* list_record_field_type)
    {
        for (const auto& i : *list_record_field_type)
        {
            i->accept(this);
        }
    }

    void VisitTypeCheck::visitInteger(Integer x)
    {
        /* Code for Integer Goes Here */
        context.SetLastInteger(x);
    }

    void VisitTypeCheck::visitChar(Char x)
    {
        /* Code for Char Goes Here */
    }

    void VisitTypeCheck::visitDouble(Double x)
    {
        /* Code for Double Goes Here */
    }

    void VisitTypeCheck::visitString(String x)
    {
        /* Code for String Goes Here */
    }

    void VisitTypeCheck::visitIdent(Ident x)
    {
        /* Code for Ident Goes Here */
    }

    void VisitTypeCheck::visitStellaIdent(StellaIdent x)
    {
        /* Code for StellaIdent Goes Here */
    }

    void VisitTypeCheck::visitExtensionName(ExtensionName x)
    {
        /* Code for ExtensionName Goes Here */
        context.ProcessLanguageExtension(x);
    }

    void VisitTypeCheck::visitMemoryAddress(MemoryAddress x)
    {
        /* Code for MemoryAddress Goes Here */
    }

    void VisitTypeCheck::visitDeclFunGeneric(DeclFunGeneric* decl_fun_generic)
    {
        /* Code For DeclFunGeneric Goes Here */
        if (decl_fun_generic->stellaident_ == "main") {
            context.IncorrectTypeOfMain();
        }

        std::shared_ptr<TypeCheck::Forall> genericFunction = std::make_shared<TypeCheck::Forall>(
            std::make_shared<TypeCheck::Function>());
        context.SetVariable(decl_fun_generic->stellaident_, genericFunction);
        context.EnterScope(decl_fun_generic->stellaident_);

        if (decl_fun_generic->listannotation_) {
            decl_fun_generic->listannotation_->accept(this);
        }
        visitStellaIdent(decl_fun_generic->stellaident_);

        if (decl_fun_generic->liststellaident_) {
            decl_fun_generic->liststellaident_->accept(this);
        }

        for (std::string& universalVarName : *(decl_fun_generic->liststellaident_)) {
            genericFunction->universalVariables.push_back(context.CreateUniversalType(universalVarName));
        }

        if (decl_fun_generic->listparamdecl_) {
            decl_fun_generic->listparamdecl_->accept(this);
        }
        if (decl_fun_generic->returntype_) {
            decl_fun_generic->returntype_->accept(this);
        }

        context.PushInferenceContext(context.GetCurrentType());

        if (decl_fun_generic->throwtype_) {
            decl_fun_generic->throwtype_->accept(this);
        }
        if (decl_fun_generic->listdecl_) {
            decl_fun_generic->listdecl_->accept(this);
        }
        if (decl_fun_generic->expr_) {
            decl_fun_generic->expr_->accept(this);
        }

        context.VerifyReturnType(context.GetCurrentType());
        context.LeaveScope();
        context.PopInferenceContext();
    }

    void VisitTypeCheck::visitTypeAbstraction(TypeAbstraction* type_abstraction)
    {
        /* Code For TypeAbstraction Goes Here */
        std::shared_ptr<TypeCheck::Forall> forall = std::make_shared<TypeCheck::Forall>();

        auto forallScopeLevel = context.generateTypeQuantifierTag();
        context.SetVariable(forallScopeLevel, std::make_shared<TypeCheck::Unknown>());
        context.EnterScope(forallScopeLevel);

        auto inferredType = context.InferWIthForall();

        if (type_abstraction->liststellaident_) {
            type_abstraction->liststellaident_->accept(this);
        }

        for (std::string& universalVarName : *(type_abstraction->liststellaident_)) {
            forall->universalVariables.push_back(context.CreateUniversalType(universalVarName));
        }

        context.PushInferenceContext(inferredType);
        if (type_abstraction->expr_) {
            type_abstraction->expr_->accept(this);
        }
        context.PopInferenceContext();

        forall->internal = context.GetCurrentType();
        context.PopTypeFromStack();

        context.LeaveScope();

        context.UpdateLastType(forall);
        context.PushTypeToEvaluationStack(forall);
    }

    void VisitTypeCheck::visitTypeApplication(TypeApplication* type_application)
    {
        /* Code For TypeApplication Goes Here */
        if (type_application->expr_) {
            type_application->expr_->accept(this);
        }
        auto genericTypeEntity = context.GetCurrentType();

        int typeCheckpoint = context.CreateStackMarker();
        if (type_application->listtype_) {
            type_application->listtype_->accept(this);
        }
        int universalStackMark = context.OpenUniversalStack(context.GetTypeSubstack(typeCheckpoint));
        context.BeginSpecialization();

        if (context.universalTypes) {
            context.AddUniversalQuantifiersToLambda(genericTypeEntity);
        }

        context.CloseUniversalStack(universalStackMark);
        context.EndSpecialization();
    }

    void VisitTypeCheck::visitTypeForAll(TypeForAll* type_for_all)
    {
        /* Code For TypeForAll Goes Here */
        std::shared_ptr<TypeCheck::Forall> forall = std::make_shared<TypeCheck::Forall>();

        auto forallScopeLevel = context.generateTypeQuantifierTag();
        context.SetVariable(forallScopeLevel, std::make_shared<TypeCheck::Unknown>());
        context.EnterScope(forallScopeLevel);

        if (type_for_all->liststellaident_) {
            type_for_all->liststellaident_->accept(this);
        }

        for (std::string& universalVarName : *(type_for_all->liststellaident_)) {
            forall->universalVariables.push_back(context.CreateUniversalType(universalVarName));
        }

        if (type_for_all->type_) {
            type_for_all->type_->accept(this);
        }

        forall->internal = context.GetCurrentType();
        context.PopTypeFromStack();

        context.LeaveScope();

        context.UpdateLastType(forall);
        context.PushTypeToEvaluationStack(forall);
    }
} // namespace Stella
