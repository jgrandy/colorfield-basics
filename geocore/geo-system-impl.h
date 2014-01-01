/* *  James Grandy *  Colorfield Digital Media Inc. * *  Copyright (c) 1999-2000 Colorfield Digital Media Inc. *  Copyright (c) 2014 James Grandy * *  Permission is hereby granted, free of charge, to any person obtaining *  a copy of this software and associated documentation files (the "Software"), *  to deal in the Software without restriction, including without limitation *  the rights to use, copy, modify, merge, publish, distribute, sublicense, *  and/or sell copies of the Software, and to permit persons to whom the Software *  is furnished to do so, subject to the following conditions: * *  The above copyright notice and this permission notice shall be included in *  all copies or substantial portions of the Software. * *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, *  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN *  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. */#ifndef __GEO_SYSTEM_IMPL_H#define __GEO_SYSTEM_IMPL_H#include "geo-system.h"#include "objective-function-tmpl.h"#include <vector>namespace cf_geocore {/*1.				2.					3.*/class system::entity_record {public:									entity_record(entity_type t, entity_subtype st, entity_id_t id)																						: type_(t), subtype_(st), id_(id), tags_(), seed_(0.) {}									entity_record(entity_type t, entity_id_t id)	: type_(t), subtype_(entity_null_subtype), id_(id), tags_(), seed_(0.) {}									entity_record(const entity_record& er)			: type_(er.type_), subtype_(er.subtype_), id_(er.id_), tags_(er.tags_), seed_(er.seed_) {}virtual								~entity_record(void)							{}				entity_record&		operator= (const entity_record &er)				{ type_ = er.type_; subtype_ = er.subtype_; id_ = er.id_; tags_ = er.tags_; seed_ = er.seed_; return *this; }				bool				operator==(const entity_record &er)				{ return (id_ == er.id_); }				bool				operator!=(const entity_record &er)				{ return (id_ != er.id_); }								entity_id_t			id(void) const									{ return id_; }				entity_type			get_entity_type(void) const						{ return type_; }				entity_subtype		get_entity_subtype(void) const					{ return subtype_; }								dictionary&			get_tags(void)									{ return tags_; }		  const dictionary&			get_tags(void) const							{ return tags_; }						  const std::string&		get_name(void) const							{ return name_; }				void				set_name(const std::string &n)					{ name_ = n; }				void				set_default_name(void);										time_t				get_seed(void) const							{ return seed_; }				void				set_seed(sim_t *sim)							{ seed_ = sim->time(); }virtual			bool				has_changed(const system */*sys*/, const cvector &/*dq*/) const { return false; }private:				entity_type			type_;				entity_subtype		subtype_;				entity_id_t			id_;				dictionary			tags_;				std::string			name_;				time_t				seed_;	// time of last change				};class system::space_record : public system::entity_record {public:		typedef space_id_t			id_t;static	  const system::entity_type	type_tag = system::entity_space_type;													space_record(id_t id, index_t dims, system::tag_t stype)																									: entity_record(entity_space_type,stype,id), 																					  dim_(dims), 																					  basis_(NULL), 																					  is_subspace_(false), subspace_tree_(NULL), indices_() 																					{}									~space_record(void)								{ if (subspace_tree_ != NULL) delete subspace_tree_; }													index_t				dimensions(void) const							{ return dim_; }				entity_subtype		space_type(void) const							{ return this->get_entity_subtype(); }												id_t				basis(void) const								{ return basis_; }				void				set_basis(id_t id)								{ basis_ = id; }								bool				is_subspace(void) const							{ return is_subspace_; }				void				set_is_subspace(bool is)						{ is_subspace_ = is; }						const std::vector<index_t>& get_indices(void) const							{ return indices_; }				void				set_indices(const std::vector<index_t> &is)		{ indices_ = is; }								struct subspace_record {				  space_id_t		subspace_;				  subspace_record*	extensions_[4];																		subspace_record(void)							: subspace_(NULL) { for (int i=0; i<4; i++) extensions_[i] = NULL; }									~subspace_record(void)							{ for (int i=0; i<4; i++) delete extensions_[i]; }				private:				  					subspace_record(const subspace_record&);				  subspace_record&	operator= (const subspace_record&);				};								subspace_record*	get_subspace_tree(void)							{ return (subspace_tree_ == NULL) ? (subspace_tree_ = new subspace_record) : subspace_tree_; }				subspace_record*	get_subspace_record(subspace_record *sr, index_t x);private:									space_record(const space_record &sr);							space_record&		operator= (const space_record &sr);											  const index_t				dim_;				id_t	 			basis_;	// ***should be const				bool				is_subspace_; // *** should be const				subspace_record*	subspace_tree_;		   std::vector<index_t>		indices_; // ***should be const};class system::locus_record : public system::entity_record {public:				typedef locus_id_t			id_t;static	  const system::entity_type	type_tag = system::entity_locus_type;											locus_record(locus_type t, id_t id)				: entity_record(entity_locus_type,t,id), space_(NULL), accessor_(NULL), dynamic_(false) {}									locus_record(const locus_record &lr)			: entity_record(lr), space_(lr.space_), accessor_(lr.accessor_), dynamic_(lr.dynamic_) {}													locus_record&		operator= (const locus_record &lr)				{ this->entity_record::operator=(lr); space_ = lr.space_; accessor_ = lr.accessor_; dynamic_ = lr.dynamic_; return *this; }								locus_type			get_locus_type(void) const						{ return this->get_entity_subtype(); }								space_id_t			space(void) const								{ return space_; }				void				set_space(space_id_t sid)						{ space_ = sid; }						  const vector_function*	accessor(void) const							{ return accessor_; }				void				set_accessor(const vector_function* vf)			{ accessor_ = vf; }								bool				is_dynamic(void) const							{ return dynamic_; }				void				set_dynamic(bool d)								{ dynamic_ = d; }				virtual			bool				has_changed(const system */*sys*/, const cvector &/*dq*/) const;private:				space_id_t			space_;		  const vector_function*	accessor_;				bool				dynamic_;};		class system::relation_record : public system::entity_record {public:		typedef system::tag_t		tag_t;		typedef relation_id_t		id_t;static	  const system::entity_type	type_tag = system::entity_relation_type;													relation_record(entity_subtype t, relation_id_t id)																									: entity_record(entity_relation_type, t, id), relation_(NULL), space_(NULL), participants_() {}									relation_record(const relation_record &rr)		: entity_record(rr), relation_(rr.relation_), space_(rr.space_), participants_(rr.participants_) {}									virtual								~relation_record(void)							{ delete relation_; }				relation_record&	operator= (const relation_record &rr)			{ this->entity_record::operator=(rr); relation_ = rr.relation_; space_ = rr.space_; participants_ = rr.participants_; return *this; }				entity_subtype		get_relation_type(void) const					{ return this->get_entity_subtype(); }						  const vector_relation*	relation(void) const							{ return relation_; }				void				set_relation(const vector_relation * r)			{ relation_ = r; }								space_id_t			space(void) const								{ return space_; }				void				set_space(space_id_t sid)						{ space_ = sid; }					 const std::vector<locus_id_t>	participants(void) const						{ return participants_; }				void				set_participants(const std::vector<locus_id_t> &p)	{ participants_ = p; }				bool				has_participant(locus_id_t lid) const;virtual			bool				has_changed(const system */*sys*/, const cvector &dq) const;private:		  const vector_relation*	relation_;				space_id_t			space_;		   std::vector<locus_id_t>	participants_;};		class system::objective_record : public system::entity_record {public:		typedef cf_simcore::objective_function<>	objective_t;		typedef objective_id_t		id_t;static	  const system::entity_type	type_tag = system::entity_objective_type;											objective_record(entity_subtype t, objective_id_t eid)																								: entity_record(entity_objective_type, t, eid), objective_(NULL) {}									objective_record(const objective_record &rr)	: entity_record(rr), objective_(rr.objective_) {}													objective_record&	operator= (const objective_record &rr)			{ this->entity_record::operator=(rr); objective_ = rr.objective_; return *this; }					objective_t*		objective(void) const							{ return objective_; }				void				set_objective(objective_t *r)					{ objective_ = r; }				private:				objective_t*		objective_;};template<class T>    T* system::get_record(entity_id_t eid, std::map<entity_id_t,system::entity_record*> &entities){	std::map<entity_id_t,system::entity_record*>::iterator p = entities.find(eid);	if (p == entities.end() || (p->second->get_entity_type() != T::type_tag))		return NULL;	else		return (T*) (p->second);}template<class T>    const T* system::get_record(entity_id_t eid, const std::map<entity_id_t,system::entity_record*> &entities){	std::map<entity_id_t,system::entity_record*>::const_iterator p = entities.find(eid);	if (p == entities.end() || (p->second->get_entity_type() != T::type_tag))		return NULL;	else		return (const T*) (p->second);}template<>    system::entity_record* system::get_record<system::entity_record>(entity_id_t eid, std::map<entity_id_t,system::entity_record*> &entities);template<>    const system::entity_record* system::get_record<system::entity_record>(entity_id_t eid, const std::map<entity_id_t,system::entity_record*> &entities);} // namespace cf_geocore#endif /* __GEO_SYSTEM_IMPL_H */